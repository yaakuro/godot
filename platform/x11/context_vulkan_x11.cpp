/*************************************************************************/
/*  context_vulkan_x11.cpp                                                   */
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
#include "context_vulkan_x11.h"

#ifdef VULKAN_ENABLED

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev) {
	ctxErrorOccurred = true;
	return 0;
}

vkf::Instance* ContextVulkan_X11::get_instance() const {
	return instance;
}

vkf::Device* ContextVulkan_X11::get_device() const {
	return device;
}

vkf::Queue* ContextVulkan_X11::get_queue() const {
	return graphics_queue;
}

vkf::CommandPool* ContextVulkan_X11::get_command_pool() const {
	return commandPool;
}

vkf::CommandBuffers* ContextVulkan_X11::get_command_buffers() const {
	return commandBuffers;
}

vkf::SwapChain* ContextVulkan_X11::get_swapchain() const {
	return swapchain;
}

void ContextVulkan_X11::release_current() {

}

void ContextVulkan_X11::make_current() {
}

void ContextVulkan_X11::swap_buffers() {
		// TODO Before swap buffer do update all uniform buffers.

		uint32_t currentBuffer;
		VkResult result = swapchain->nextImage(currentBuffer, present_semaphore);
		if(VK_SUCCESS == result || VK_SUBOPTIMAL_KHR == result) {
			//
			// Submit the commands.
			//
			graphics_queue->submit(commandBuffers->getCommandBuffer(currentBuffer), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, render_semaphore, present_semaphore);

			//
			// When ready present the framebuffer.
			//
			VkResult result = swapchain->present(present_queue, currentBuffer, render_semaphore);
			if(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR) {
				result = vkQueueWaitIdle(*present_queue);
			}
		}
}

Error ContextVulkan_X11::initialize() {
	int (*oldHandler)(Display *, XErrorEvent *) = XSetErrorHandler(&ctxErrorHandler);

	XSetWindowAttributes swa {};
	//swa.colormap = XCreateColormap(x11_display, RootWindow(x11_display, DefaultScreen(x11_display)), vi->visual, AllocNone);
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask;

	x11_window = XCreateWindow(x11_display, RootWindow(x11_display, DefaultScreen(x11_display)), 0, 0, OS::get_singleton()->get_video_mode().width, OS::get_singleton()->get_video_mode().height, 0, CopyFromParent, InputOutput, CopyFromParent, CWBorderPixel | CWColormap | CWEventMask, &swa);
	ERR_FAIL_COND_V(!x11_window, ERR_UNCONFIGURED);
	XMapWindow(x11_display, x11_window);
	XSync(x11_display, False);
	XSetErrorHandler(oldHandler);

	vkf::init();

	windows = new vkf::Windows("GodotEngine", OS::get_singleton()->get_video_mode().width, OS::get_singleton()->get_video_mode().height);
	if(windows->init(x11_display, x11_window) != VK_SUCCESS) {
		return FAILED;
	}

	instance = new vkf::Instance(windows->getTitle());
	if(instance->init() != VK_SUCCESS) {
		return FAILED;
	}

	device = new vkf::Device(instance);
	if(device->init() != VK_SUCCESS) {
		return FAILED;
	}

	surface = new vkf::Surface(device, windows);
	if(surface->init() != VK_SUCCESS) {
		return FAILED;
	}

	swapchain = new vkf::SwapChain(surface);
	if(swapchain->init() != VK_SUCCESS) {
		return FAILED;
	}

	graphics_queue = new vkf::Queue(device, device->getGraphicsQueueIndex(), 0);
	if(graphics_queue->init() != VK_SUCCESS) {
		return FAILED;
	}

	present_queue = new vkf::Queue(device, device->getGraphicsQueueIndex(), 0);
	if(present_queue->init() != VK_SUCCESS) {
		return FAILED;
	}

	present_semaphore = new vkf::Semaphore(device);
	if(present_semaphore->init() != VK_SUCCESS) {
		return FAILED;
	}
	
	render_semaphore = new vkf::Semaphore(device);
	if(render_semaphore->init() != VK_SUCCESS) {
		return FAILED;
	}

	commandPool = new vkf::CommandPool(device);
	if(commandPool->init() != VK_SUCCESS) {
		return FAILED;
	}

	commandBuffers = memnew(vkf::CommandBuffers(device, commandPool, 3));
	if(commandBuffers->init() != VK_SUCCESS) {
		return FAILED;
	}

	return OK;
}

int ContextVulkan_X11::get_window_width() {

	XWindowAttributes xwa;
	XGetWindowAttributes(x11_display, x11_window, &xwa);

	return xwa.width;
}

int ContextVulkan_X11::get_window_height() {
	XWindowAttributes xwa;
	XGetWindowAttributes(x11_display, x11_window, &xwa);

	return xwa.height;
}

void ContextVulkan_X11::set_use_vsync(bool p_use) {

}

bool ContextVulkan_X11::is_using_vsync() const {
	return false;
}

ContextVulkan_X11::ContextVulkan_X11(::Display *p_x11_display, ::Window &p_x11_window, const OS::VideoMode &p_default_video_mode, bool p_opengl_3_context)
	: x11_window(p_x11_window){
	default_video_mode = p_default_video_mode;
	x11_display = p_x11_display;
}

ContextVulkan_X11::~ContextVulkan_X11() {
	present_semaphore->destroy();
	render_semaphore->destroy();
	commandBuffers->destroy();
	commandPool->destroy();
	surface->destroy();
	device->destroy();
	instance->destroy();
	delete present_semaphore;
	delete render_semaphore;
	delete commandBuffers;
	delete commandPool;
	delete surface;
	delete device;
	delete instance;
	vkf::destroy();
}

#endif

