/*************************************************************************/
/*  rasterizer_vulkan.cpp                                                 */
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

#include "os/os.h"

#include "vulkan_framework.h"
#include "rasterizer_vulkan.h"
#include "project_settings.h"

vkf::Instance* RasterizerVulkan::get_instance() {
	return instance;
}

vkf::Device* RasterizerVulkan::get_device() {
	return device;
}

vkf::SwapChain* RasterizerVulkan::get_swapchain() {
	return swapchain;
}

vkf::Queue* RasterizerVulkan::get_queue() {
	return queue;
}

vkf::CommandPool* RasterizerVulkan::get_command_pool() {
	return command_pool;
}

vkf::CommandBuffers* RasterizerVulkan::get_command_buffers() {
	return command_buffers;
}

RasterizerStorage *RasterizerVulkan::get_storage() {
	return storage;
}

RasterizerCanvas *RasterizerVulkan::get_canvas() {
	return canvas;
}

RasterizerScene *RasterizerVulkan::get_scene() {
	return scene;
}

void RasterizerVulkan::initialize() {

	if(OS::get_singleton()->is_stdout_verbose()) {
		print_line("Using Vulkan video driver");
	}

	storage->initialize();
	canvas->initialize();
	scene->initialize();
}

void RasterizerVulkan::begin_frame(double frame_step) {
}

void RasterizerVulkan::set_current_render_target(RID p_render_target) {
}

void RasterizerVulkan::restore_render_target() {
}

void RasterizerVulkan::clear_render_target(const Color &p_color) {
}

void RasterizerVulkan::set_boot_image(const Ref<Image> &p_image, const Color &p_color, bool p_scale) {

		if (p_image.is_null() || p_image->empty())
			return;

	 	begin_frame(0.0f);

	 	int window_w = OS::get_singleton()->get_video_mode(0).width;
	 	int window_h = OS::get_singleton()->get_video_mode(0).height;

	 	canvas->canvas_begin();

		RID texture = storage->texture_create();
		storage->texture_allocate(texture, p_image->get_width(), p_image->get_height(), 0, p_image->get_format(), VS::TEXTURE_TYPE_2D, VS::TEXTURE_FLAG_FILTER);
		storage->texture_set_data(texture, p_image);

		Rect2 imgrect(0, 0, p_image->get_width(), p_image->get_height());
		Rect2 screenrect;
		if (p_scale) {

		if (window_w > window_h) {
			//scale horizontally
			screenrect.size.y = window_h;
			screenrect.size.x = imgrect.size.x * window_h / imgrect.size.y;
			screenrect.position.x = (window_w - screenrect.size.x) / 2;

		} else {
			//scale vertically
			screenrect.size.x = window_w;
			screenrect.size.y = imgrect.size.y * window_w / imgrect.size.x;
			screenrect.position.y = (window_h - screenrect.size.y) / 2;
		}
		} else {

		screenrect = imgrect;
		screenrect.position += ((Size2(window_w, window_h) - screenrect.size) / 2.0).floor();
		}
	 canvas->canvas_end();

	 storage->free(texture); // free since it's only one frame that stays there

	 OS::get_singleton()->swap_buffers();
}

void RasterizerVulkan::blit_render_target_to_screen(RID p_render_target, const Rect2 &p_screen_rect, int p_screen) {
	 canvas->canvas_begin();
	 canvas->canvas_end();
}

vkf::Instance* RasterizerVulkan::instance = nullptr;
vkf::Device* RasterizerVulkan::device = nullptr;
vkf::SwapChain* RasterizerVulkan::swapchain = nullptr;
vkf::Queue* RasterizerVulkan::queue = nullptr;
vkf::CommandPool* RasterizerVulkan::command_pool = nullptr;
vkf::CommandBuffers* RasterizerVulkan::command_buffers = nullptr;

void RasterizerVulkan::end_frame(bool p_swap_buffers) {
if (OS::get_singleton()->is_layered_allowed()) {
		if (OS::get_singleton()->get_window_per_pixel_transparency_enabled()) {
#if (defined WINDOWS_ENABLED) && !(defined UWP_ENABLED)
			Size2 wndsize = OS::get_singleton()->get_layered_buffer_size();
			uint8_t *data = OS::get_singleton()->get_layered_buffer_data();
			if (data) {
				glReadPixels(0, 0, wndsize.x, wndsize.y, GL_BGRA, GL_UNSIGNED_BYTE, data);
				OS::get_singleton()->swap_layered_buffer();

				return;
			}
#endif
		} else {
			//clear alpha
		//	glColorMask(false, false, false, true);
		//	glClearColor(0, 0, 0, 1);
		//	glClear(GL_COLOR_BUFFER_BIT);
		//	glColorMask(true, true, true, true);
		}
	}

	if (p_swap_buffers)
		OS::get_singleton()->swap_buffers();
	else {
	//	glFinish();
	}
}

void RasterizerVulkan::finalize() {

	storage->finalize();
	canvas->finalize();
}

Rasterizer *RasterizerVulkan::_create_current() {

	return memnew(RasterizerVulkan);
}

void RasterizerVulkan::make_current() {
	_create_func = _create_current;
}

void RasterizerVulkan::register_config() {

	GLOBAL_DEF("rendering/quality/filters/use_nearest_mipmap_filter", false);
	GLOBAL_DEF("rendering/quality/filters/anisotropic_filter_level", 4.0);
}

RasterizerVulkan::RasterizerVulkan() {

	storage = memnew(RasterizerStorageVulkan);
	canvas = memnew(RasterizerCanvasVulkan);
	scene = memnew(RasterizerSceneVulkan);
	canvas->storage = storage;
	canvas->scene_render = scene;
	storage->canvas = canvas;
	scene->storage = storage;
	storage->scene = scene;
}

RasterizerVulkan::~RasterizerVulkan() {

	memdelete(storage);
	memdelete(canvas);
}

void RasterizerVulkan::set_vulkan_instance(vkf::Instance* inst) {
	instance = inst;
}

void RasterizerVulkan::set_vulkan_device(vkf::Device* dev) {
	device = dev;
}

void RasterizerVulkan::set_vulkan_queue(vkf::Queue* qu) {
	queue = qu;
}

void RasterizerVulkan::set_vulkan_command_pool(vkf::CommandPool* cp) {
	command_pool = cp;
}

void RasterizerVulkan::set_vulkan_command_buffers(vkf::CommandBuffers* cbs) {
	command_buffers = cbs;
}

void RasterizerVulkan::set_vulkan_swapchain(vkf::SwapChain* sc) {
	swapchain = sc;
}