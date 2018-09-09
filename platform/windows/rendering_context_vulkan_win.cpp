/*************************************************************************/
/*  rendering_context_vulkan_win.cpp                                     */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
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
#include <windows.h>

#include "glad_vulkan_win.h"

#include "vma_usage.h"
#include "os_windows.h"

#include "platform/windows/rendering_context_vulkan_win.h"

//#if defined(OPENGL_ENABLED) || defined(GLES_ENABLED)

void RenderingContextVulkan_Win::release_current() {
}

void RenderingContextVulkan_Win::make_current() {
}

void RenderingContextVulkan_Win::swap_buffers() {
}

int RenderingContextVulkan_Win::get_window_width() {
	return OS::get_singleton()->get_video_mode(0).width;
}

int RenderingContextVulkan_Win::get_window_height() {
	return OS::get_singleton()->get_video_mode(0).height;
}

Error RenderingContextVulkan_Win::initialize() {

	Error error;
	if ((error = _create_instance()) != OK) {
		return error;
	}

	_enable_debug();

	if ((error = create_surface()) != OK) {
		return error;
	}
	if ((error = _pick_physical_device()) != OK) {
		return error;
	}
	if ((error = _create_logical_device()) != OK) {
		return error;
	}
	if ((error = _create_swap_chain()) != OK) {
		return error;
	}

	return OK;
}

void RenderingContextVulkan_Win::set_use_vsync(bool p_use) {
}

bool RenderingContextVulkan_Win::is_using_vsync() const {
	return false;
}

RenderingContextVulkan_Win::RenderingContextVulkan_Win(HWND hwnd) {

	hWnd = hwnd;
	use_vsync = false;
	device_extensions.insert(String(VK_KHR_SWAPCHAIN_EXTENSION_NAME).utf8());
	validation_layers.insert(String("VK_LAYER_LUNARG_standard_validation").utf8());

	glad_vk_version = gladLoaderLoadVulkan(NULL, NULL, NULL);
	if (!glad_vk_version) {
		ERR_FAIL("Unable to load Vulkan symbols!\n",
				"gladLoad Failure");
	}
}

RenderingContextVulkan_Win::~RenderingContextVulkan_Win() {
}

Error RenderingContextVulkan_Win::create_surface() {
	VkWin32SurfaceCreateInfoKHR create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	create_info.hwnd = hWnd;
	create_info.hinstance = GetModuleHandle(NULL);

	PFN_vkCreateWin32SurfaceKHR CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(*_get_instance(), "vkCreateWin32SurfaceKHR");

	if (!CreateWin32SurfaceKHR || CreateWin32SurfaceKHR(*_get_instance(), &create_info, NULL, &surface) != VK_SUCCESS) {
		ERR_FAIL_V(ERR_CANT_CREATE, "Can't Create Window Surface.");
	}
	return OK;
}

//#endif