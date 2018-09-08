/*************************************************************************/
/*  rasterizer_canvas_gles3.cpp                                          */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2018 Cengiz Terzibas (Yaakuro)                     */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "rasterizer_canvas_vulkan.h"
#include "rasterizer_storage_vulkan.h"
#include "rasterizer_vulkan.h"
#include "servers/visual/visual_server_raster.h"
#include "vulkan_framework.h"

RasterizerCanvasVulkan::~RasterizerCanvasVulkan() {}

struct WindowMarginVertex {
	float x, y, z, w;
	float ts, tv;
	float r, g, b, a;
};

struct UniformBufferStruct {
	float projectionMatrix[16];
	float modelMatrix[16];
	float viewMatrix[16];
};

void RasterizerCanvasVulkan::initialize() {
	currentBufferIndex = 0;

	window_margin_vb = new vkf::VertexBuffer(RasterizerVulkan::get_device(), vkf::BufferSize(4 * sizeof(WindowMarginVertex)));
	window_margin_vb->addElement(vkf::BindingPoint(0), vkf::LocationPoint(0), VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(WindowMarginVertex, x));
	window_margin_vb->addElement(vkf::BindingPoint(0), vkf::LocationPoint(1), VK_FORMAT_R32G32_SFLOAT, offsetof(WindowMarginVertex, ts));
	window_margin_vb->addElement(vkf::BindingPoint(0), vkf::LocationPoint(2), VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(WindowMarginVertex, r));
	window_margin_vb->init();

	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};

	window_margin_ib = new vkf::IndexBuffer(RasterizerVulkan::get_device(), indices.size(), vkf::BufferSize(indices.size() * sizeof(uint32_t)));
	window_margin_ib->init();
	window_margin_ib->upload((uint8_t*)indices.data(), vkf::BufferSize(indices.size() * sizeof(uint32_t)));

	uniformBuffer = new vkf::UniformBuffer(RasterizerVulkan::get_device(), vkf::BufferSize(sizeof(UniformBufferStruct)));
	uniformBuffer->init();

	descriptorPool = new vkf::DescriptorPool(RasterizerVulkan::get_device());
	descriptorPool->add(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
	descriptorPool->init();
	
	descriptorSetLayout = new vkf::DescriptorSetLayout(RasterizerVulkan::get_device());
	descriptorSetLayout->add(vkf::BindingPoint(0), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
	descriptorSetLayout->init();

	descriptorSet = new vkf::DescriptorSet(RasterizerVulkan::get_device(), descriptorPool, descriptorSetLayout);
	descriptorSet->bind(vkf::BindingPoint(0), uniformBuffer);
	descriptorSet->init();

	pipeline = new vkf::Pipeline(RasterizerVulkan::get_device(), descriptorSetLayout, &RasterizerVulkan::get_swapchain()->getRenderPass(), RasterizerVulkan::get_swapchain()->getExtent2D());
	pipeline->addVertexState(window_margin_vb);
	// TODO Shader modules must be handled.
	//pipeline->init(); 

}

void RasterizerCanvasVulkan::finalize() {
	window_margin_vb->destroy();
	window_margin_ib->destroy();
	uniformBuffer->destroy();
	descriptorPool->destroy();
	descriptorSetLayout->destroy();
	descriptorSet->destroy();
	pipeline->destroy();

	delete window_margin_vb;
	delete window_margin_ib;
	delete uniformBuffer;
	delete descriptorPool;
	delete descriptorSetLayout;
	delete descriptorSet;
	delete pipeline;

	window_margin_vb = NULL;
	window_margin_ib = NULL;
	uniformBuffer = NULL;
	descriptorPool = NULL;
	descriptorSetLayout = NULL;
	descriptorSet = NULL;
	pipeline = NULL;
}

RID RasterizerCanvasVulkan::light_internal_create() {}
void RasterizerCanvasVulkan::light_internal_update(RID p_rid, Light *p_light) { }
void RasterizerCanvasVulkan::light_internal_free(RID p_rid) {}

void RasterizerCanvasVulkan::canvas_begin() {
	VkCommandBufferBeginInfo commandBufferBeginInfo {};
	commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	std::array<VkClearValue, 2> clearValues {};
	clearValues[0].color = {{0.0f, 1.0f, 0.0f, 1.0f}};
	clearValues[1].depthStencil = { 1.0f, 0 };

	VkRenderPassBeginInfo renderPassBeginInfo {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.renderPass = RasterizerVulkan::get_swapchain()->getRenderPass();
	renderPassBeginInfo.renderArea.offset.x = 0;
	renderPassBeginInfo.renderArea.offset.y = 0;
	renderPassBeginInfo.renderArea.extent = RasterizerVulkan::get_swapchain()->getExtent2D();
	renderPassBeginInfo.clearValueCount = clearValues.size();
	renderPassBeginInfo.pClearValues = clearValues.data();
	renderPassBeginInfo.framebuffer = RasterizerVulkan::get_swapchain()->getFramebuffer(currentBufferIndex);

	CurrentCommandBuffer = RasterizerVulkan::get_command_buffers()->getCommandBuffer(currentBufferIndex);

	vkBeginCommandBuffer(*CurrentCommandBuffer, &commandBufferBeginInfo);
	vkCmdBeginRenderPass(*CurrentCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void RasterizerCanvasVulkan::canvas_end() {
	vkCmdEndRenderPass(*CurrentCommandBuffer);
	vkEndCommandBuffer(*CurrentCommandBuffer);
	currentBufferIndex++;
	currentBufferIndex %= RasterizerVulkan::get_swapchain()->getImageCount();
}

void RasterizerCanvasVulkan::canvas_render_items(Item *p_item_list, int p_z, const Color &p_modulate, Light *p_light, const Transform2D &p_base_transform) {}
void RasterizerCanvasVulkan::canvas_debug_viewport_shadows(Light *p_lights_with_shadow) {}
void RasterizerCanvasVulkan::canvas_light_shadow_buffer_update(RID p_buffer, const Transform2D &p_light_xform, int p_light_mask, float p_near, float p_far, LightOccluderInstance *p_occluders, CameraMatrix *p_xform_cache) {}
void RasterizerCanvasVulkan::reset_canvas() {}

void RasterizerCanvasVulkan::draw_window_margins(int *p_margins, RID *p_margin_textures) {
	Vector2 window_size = OS::get_singleton()->get_window_size();
	int window_h = window_size.height;
	int window_w = window_size.width;

	VkViewport viewport {};
	viewport.width = window_size.width;
	viewport.height = window_size.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	printf("draw_window_margins\n");
	canvas_begin();
	{
		vkCmdSetViewport(*CurrentCommandBuffer, 0, 1, &viewport);

//		vkCmdBindDescriptorSets(*CurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipelineLayout(), 0, 1, *descriptorSet, 0, nullptr);
//		vkCmdBindPipeline(*CurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline);

		if (p_margin_textures[MARGIN_LEFT].is_valid()) {
			// _bind_canvas_texture(black_image[MARGIN_LEFT], RID());
			 Size2 sz(storage->texture_get_width(p_margin_textures[MARGIN_LEFT]), storage->texture_get_height(p_margin_textures[MARGIN_LEFT]));
			 draw_generic_textured_rect(Rect2(0, 0, p_margins[MARGIN_LEFT], window_h), Rect2(0, 0, sz.x, sz.y));
			
		} else if (p_margins[MARGIN_LEFT]) {
			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_2D, storage->resources.black_tex);
			// draw_generic_textured_rect(Rect2(0, 0, p_margins[MARGIN_LEFT], window_h), Rect2(0, 0, 1, 1));
		}
		if (p_margin_textures[MARGIN_RIGHT].is_valid()) {
			// _bind_canvas_texture(black_image[MARGIN_RIGHT], RID());
			// Size2 sz(storage->texture_get_width(p_margin_textures[MARGIN_RIGHT]), storage->texture_get_height(p_margin_textures[MARGIN_RIGHT]));
			// draw_generic_textured_rect(Rect2(window_w - p_margins[MARGIN_RIGHT], 0, p_margins[MARGIN_RIGHT], window_h), Rect2(0, 0, sz.x, sz.y));
		} else if (p_margins[MARGIN_RIGHT]) {
			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_2D, storage->resources.black_tex);

			// draw_generic_textured_rect(Rect2(window_w - p_margins[MARGIN_RIGHT], 0, p_margins[MARGIN_RIGHT], window_h), Rect2(0, 0, 1, 1));
		}

		if (p_margin_textures[MARGIN_TOP].is_valid()) {
			// _bind_canvas_texture(black_image[MARGIN_TOP], RID());

			// Size2 sz(storage->texture_get_width(p_margin_textures[MARGIN_TOP]), storage->texture_get_height(p_margin_textures[MARGIN_TOP]));
			// draw_generic_textured_rect(Rect2(0, 0, window_w, p_margins[MARGIN_TOP]), Rect2(0, 0, sz.x, sz.y));

		} else if (p_margins[MARGIN_TOP]) {
			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_2D, storage->resources.black_tex);

			// draw_generic_textured_rect(Rect2(0, 0, window_w, p_margins[MARGIN_TOP]), Rect2(0, 0, 1, 1));
		}

		if (p_margin_textures[MARGIN_BOTTOM].is_valid()) {

			// _bind_canvas_texture(black_image[MARGIN_BOTTOM], RID());

			// Size2 sz(storage->texture_get_width(p_margin_textures[MARGIN_BOTTOM]), storage->texture_get_height(p_margin_textures[MARGIN_BOTTOM]));
			// draw_generic_textured_rect(Rect2(0, window_h - p_margins[MARGIN_BOTTOM], window_w, p_margins[MARGIN_BOTTOM]), Rect2(0, 0, sz.x, sz.y));

		} else if (p_margins[MARGIN_BOTTOM]) {

			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_2D, storage->resources.black_tex);

			// draw_generic_textured_rect(Rect2(0, window_h - p_margins[MARGIN_BOTTOM], window_w, p_margins[MARGIN_BOTTOM]), Rect2(0, 0, 1, 1));
		}
	}
	canvas_end();
}

void RasterizerCanvasVulkan::draw_generic_textured_rect(const Rect2 &p_rect, const Rect2 &p_src) {

	// state.canvas_shader.set_uniform(CanvasShaderGLES3::DST_RECT, Color(p_rect.position.x, p_rect.position.y, p_rect.size.x, p_rect.size.y));
	// state.canvas_shader.set_uniform(CanvasShaderGLES3::SRC_RECT, Color(p_src.position.x, p_src.position.y, p_src.size.x, p_src.size.y));
	// state.canvas_shader.set_uniform(CanvasShaderGLES3::CLIP_RECT_UV, false);

	// glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
