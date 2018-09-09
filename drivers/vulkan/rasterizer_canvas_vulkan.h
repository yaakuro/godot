/*************************************************************************/
/*  rasterizer_canvas_vulkan.h                                           */
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

#ifndef RASTERIZER_CANVAS_VULKAN_H
#define RASTERIZER_CANVAS_VULKAN_H

#include "servers/visual/rasterizer.h"
#include "vulkan_framework.h"
#include "shaders/canvas.glsl.gen.h"

class RasterizerStorageVulkan;
class RasterizerSceneVulkan;

class RasterizerCanvasVulkan : public RasterizerCanvas {
	public:
		virtual ~RasterizerCanvasVulkan();

		void initialize();
		void finalize();

		RID light_internal_create() override final;
		void light_internal_update(RID p_rid, Light *p_light) override final;
		void light_internal_free(RID p_rid) override final;
		void canvas_begin() override final;
		void canvas_end() override final;
		void canvas_render_items(Item *p_item_list, int p_z, const Color &p_modulate, Light *p_light, const Transform2D &p_base_transform) override final;
		void canvas_debug_viewport_shadows(Light *p_lights_with_shadow) override final;
		void canvas_light_shadow_buffer_update(RID p_buffer, const Transform2D &p_light_xform, int p_light_mask, float p_near, float p_far, LightOccluderInstance *p_occluders, CameraMatrix *p_xform_cache) override final;
		void draw_window_margins(int *p_margins, RID *p_margin_textures) override final;
		void reset_canvas() override final;

		void draw_generic_textured_rect(const Rect2 &p_rect, const Rect2 &p_src);

		CanvasShaderVulkan canvas_shader;
		
		RasterizerStorageVulkan* storage;
		RasterizerSceneVulkan* scene_render;
		uint32_t currentBufferIndex;
		vkf::CommandBuffer* CurrentCommandBuffer;
		vkf::VertexBuffer* window_margin_vb;
		vkf::IndexBuffer* window_margin_ib;
		vkf::UniformBuffer* uniformBuffer;

		vkf::DescriptorPool* descriptorPool;
		vkf::DescriptorSetLayout* descriptorSetLayout;
		vkf::DescriptorSet* descriptorSet;
		vkf::Pipeline* pipeline;
};

#endif
