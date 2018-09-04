/*************************************************************************/
/*  rendering_context_vulkan_win.h                                       */
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

#ifndef RENDERING_CONTEXT_VULKAN_WIN_H
#define RENDERING_CONTEXT_VULKAN_WIN_H

//#if defined(OPENGL_ENABLED) || defined(GLES_ENABLED)
#include "typedefs.h"

#include "drivers/vulkan/rendering_context_vulkan.h"
#include "thirdparty/glad2/include/glad/vulkan.h"
#include "vma_usage.h"

class RenderingContextVulkan_Win : public RenderingContextVulkan {
private:
	HWND hWnd;

	unsigned int pixel_format;
	bool use_vsync;
	int glad_vk_version = 0;

public:
	VmaAllocator allocator;
	VmaAllocator *get_allocator() {
		return &allocator;
	}

	void allocate_vma() {
		VmaAllocatorCreateInfo allocator_info = {};

		VmaVulkanFunctions vma_vulkan_functions;
		vma_vulkan_functions.vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties;
		vma_vulkan_functions.vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties;
		vma_vulkan_functions.vkAllocateMemory = vkAllocateMemory;
		vma_vulkan_functions.vkFreeMemory = vkFreeMemory;
		vma_vulkan_functions.vkMapMemory = vkMapMemory;
		vma_vulkan_functions.vkUnmapMemory = vkUnmapMemory;
		vma_vulkan_functions.vkBindBufferMemory = vkBindBufferMemory;
		vma_vulkan_functions.vkBindImageMemory = vkBindImageMemory;
		vma_vulkan_functions.vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements;
		vma_vulkan_functions.vkGetImageMemoryRequirements = vkGetImageMemoryRequirements;
		vma_vulkan_functions.vkCreateBuffer = vkCreateBuffer;
		vma_vulkan_functions.vkDestroyBuffer = vkDestroyBuffer;
		vma_vulkan_functions.vkCreateImage = vkCreateImage;
		vma_vulkan_functions.vkDestroyImage = vkDestroyImage;
		vma_vulkan_functions.vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2KHR;
		vma_vulkan_functions.vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2KHR;

		allocator_info.pVulkanFunctions = &vma_vulkan_functions;
		allocator_info.physicalDevice = _get_physical_device();
		allocator_info.device = *_get_device();

		vmaCreateAllocator(&allocator_info, &allocator);
	}

public:
	virtual void release_current();
	virtual void make_current();
	virtual void swap_buffers();
	virtual int get_window_width();
	virtual int get_window_height();

	virtual Error initialize();

	virtual void set_use_vsync(bool p_use);
	virtual bool is_using_vsync() const;

	RenderingContextVulkan_Win(HWND hwnd);
	~RenderingContextVulkan_Win();

public:
	Error create_surface();
};

//#endif

#endif
