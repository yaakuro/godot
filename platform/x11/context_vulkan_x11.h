/*************************************************************************/
/*  context_vulkan_x11.h                                                     */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Cengiz Terzibas (Yaakuro)                     */
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
#ifndef CONTEXT_VULKAN_X11_H
#define CONTEXT_VULKAN_X11_H

/**
	@author Cengiz Terzibas <yaakuro@codeposer.net>
*/
#ifdef VULKAN_ENABLED

#include "drivers/vulkan_context/context_vulkan.h"
#include "os/os.h"

#include "drivers/vulkan/vulkan_framework_windows.h"
#include "drivers/vulkan/vulkan_framework.h"

#include <string>
#include <iostream>
#include <vector>


class ContextVulkan_X11 : public ContextVulkan {

	OS::VideoMode default_video_mode;
	//::Colormap x11_colormap;
	::Display *x11_display;
	::Window &x11_window;
	vkf::Instance* instance;
	vkf::Device* device;
	vkf::Windows* windows;
	vkf::Surface* surface;
	vkf::SwapChain* swapchain;
	vkf::Queue* graphics_queue;
	vkf::Queue* present_queue;
	vkf::CommandPool* commandPool;
	vkf::CommandBuffers* commandBuffers;
	vkf::Semaphore* present_semaphore;
	vkf::Semaphore* render_semaphore;

public:
	vkf::Instance* get_instance() const;
	vkf::Device* get_device() const;
	vkf::Queue* get_queue() const;
	vkf::CommandPool* get_command_pool() const;
	vkf::CommandBuffers* get_command_buffers() const;
	vkf::SwapChain* get_swapchain() const;

	virtual void release_current();
	virtual void make_current();
	virtual void swap_buffers();
	virtual int get_window_width();
	virtual int get_window_height();

	virtual Error initialize();

	virtual void set_use_vsync(bool p_use);
	virtual bool is_using_vsync() const;

	ContextVulkan_X11(::Display *p_x11_display, ::Window &p_x11_window, const OS::VideoMode &p_default_video_mode, bool p_opengl_3_context);
	virtual ~ContextVulkan_X11();
};

#endif

#endif

