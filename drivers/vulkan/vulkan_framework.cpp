/*
	Vulkan Framework Copyright (c) 2017 - 2018 Cengiz Terzibas

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so, subject to the
	following conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.

*/

#include "vulkan_framework_windows.h"
#include "vulkan_framework.h"

#ifdef __linux__
#include <dlfcn.h>
#define VKF_FUNCTION_LOAD(LIBRARY, entrypoint) entrypoint = (PFN_##entrypoint)dlsym(LIBRARY, #entrypoint);
#elif defined(WIN32)
#include <windows.h>
#define VKF_FUNCTION_LOAD(LIBRARY, entrypoint) entrypoint = (PFN_##entrypoint)GetProcAddress(static_cast<HMODULE>(LIBRARY), #entrypoint);
#endif

#include <string>
#include <cstdint>

// -----------------------------------------------------------------------------
// Vulkan 1.0
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkCreateInstance)
VKF_FUNCTION_DEFINE(vkDestroyInstance)
VKF_FUNCTION_DEFINE(vkEnumeratePhysicalDevices)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFeatures)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFormatProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceImageFormatProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceQueueFamilyProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceMemoryProperties)
VKF_FUNCTION_DEFINE(vkGetInstanceProcAddr)
VKF_FUNCTION_DEFINE(vkGetDeviceProcAddr)
VKF_FUNCTION_DEFINE(vkCreateDevice)
VKF_FUNCTION_DEFINE(vkDestroyDevice)
VKF_FUNCTION_DEFINE(vkEnumerateInstanceExtensionProperties)
VKF_FUNCTION_DEFINE(vkEnumerateDeviceExtensionProperties)
VKF_FUNCTION_DEFINE(vkEnumerateInstanceLayerProperties)
VKF_FUNCTION_DEFINE(vkEnumerateDeviceLayerProperties)
VKF_FUNCTION_DEFINE(vkGetDeviceQueue)
VKF_FUNCTION_DEFINE(vkQueueSubmit)
VKF_FUNCTION_DEFINE(vkQueueWaitIdle)
VKF_FUNCTION_DEFINE(vkDeviceWaitIdle)
VKF_FUNCTION_DEFINE(vkAllocateMemory)
VKF_FUNCTION_DEFINE(vkFreeMemory)
VKF_FUNCTION_DEFINE(vkMapMemory)
VKF_FUNCTION_DEFINE(vkUnmapMemory)
VKF_FUNCTION_DEFINE(vkFlushMappedMemoryRanges)
VKF_FUNCTION_DEFINE(vkInvalidateMappedMemoryRanges)
VKF_FUNCTION_DEFINE(vkGetDeviceMemoryCommitment)
VKF_FUNCTION_DEFINE(vkBindBufferMemory)
VKF_FUNCTION_DEFINE(vkBindImageMemory)
VKF_FUNCTION_DEFINE(vkGetBufferMemoryRequirements)
VKF_FUNCTION_DEFINE(vkGetImageMemoryRequirements)
VKF_FUNCTION_DEFINE(vkGetImageSparseMemoryRequirements)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSparseImageFormatProperties)
VKF_FUNCTION_DEFINE(vkQueueBindSparse)
VKF_FUNCTION_DEFINE(vkCreateFence)
VKF_FUNCTION_DEFINE(vkDestroyFence)
VKF_FUNCTION_DEFINE(vkResetFences)
VKF_FUNCTION_DEFINE(vkGetFenceStatus)
VKF_FUNCTION_DEFINE(vkWaitForFences)
VKF_FUNCTION_DEFINE(vkCreateSemaphore)
VKF_FUNCTION_DEFINE(vkDestroySemaphore)
VKF_FUNCTION_DEFINE(vkCreateEvent)
VKF_FUNCTION_DEFINE(vkDestroyEvent)
VKF_FUNCTION_DEFINE(vkGetEventStatus)
VKF_FUNCTION_DEFINE(vkSetEvent)
VKF_FUNCTION_DEFINE(vkResetEvent)
VKF_FUNCTION_DEFINE(vkCreateQueryPool)
VKF_FUNCTION_DEFINE(vkDestroyQueryPool)
VKF_FUNCTION_DEFINE(vkGetQueryPoolResults)
VKF_FUNCTION_DEFINE(vkCreateBuffer)
VKF_FUNCTION_DEFINE(vkDestroyBuffer)
VKF_FUNCTION_DEFINE(vkCreateBufferView)
VKF_FUNCTION_DEFINE(vkDestroyBufferView)
VKF_FUNCTION_DEFINE(vkCreateImage)
VKF_FUNCTION_DEFINE(vkDestroyImage)
VKF_FUNCTION_DEFINE(vkGetImageSubresourceLayout)
VKF_FUNCTION_DEFINE(vkCreateImageView)
VKF_FUNCTION_DEFINE(vkDestroyImageView)
VKF_FUNCTION_DEFINE(vkCreateShaderModule)
VKF_FUNCTION_DEFINE(vkDestroyShaderModule)
VKF_FUNCTION_DEFINE(vkCreatePipelineCache)
VKF_FUNCTION_DEFINE(vkDestroyPipelineCache)
VKF_FUNCTION_DEFINE(vkGetPipelineCacheData)
VKF_FUNCTION_DEFINE(vkMergePipelineCaches)
VKF_FUNCTION_DEFINE(vkCreateGraphicsPipelines)
VKF_FUNCTION_DEFINE(vkCreateComputePipelines)
VKF_FUNCTION_DEFINE(vkDestroyPipeline)
VKF_FUNCTION_DEFINE(vkCreatePipelineLayout)
VKF_FUNCTION_DEFINE(vkDestroyPipelineLayout)
VKF_FUNCTION_DEFINE(vkCreateSampler)
VKF_FUNCTION_DEFINE(vkDestroySampler)
VKF_FUNCTION_DEFINE(vkCreateDescriptorSetLayout)
VKF_FUNCTION_DEFINE(vkDestroyDescriptorSetLayout)
VKF_FUNCTION_DEFINE(vkCreateDescriptorPool)
VKF_FUNCTION_DEFINE(vkDestroyDescriptorPool)
VKF_FUNCTION_DEFINE(vkResetDescriptorPool)
VKF_FUNCTION_DEFINE(vkAllocateDescriptorSets)
VKF_FUNCTION_DEFINE(vkFreeDescriptorSets)
VKF_FUNCTION_DEFINE(vkUpdateDescriptorSets)
VKF_FUNCTION_DEFINE(vkCreateFramebuffer)
VKF_FUNCTION_DEFINE(vkDestroyFramebuffer)
VKF_FUNCTION_DEFINE(vkCreateRenderPass)
VKF_FUNCTION_DEFINE(vkDestroyRenderPass)
VKF_FUNCTION_DEFINE(vkGetRenderAreaGranularity)
VKF_FUNCTION_DEFINE(vkCreateCommandPool)
VKF_FUNCTION_DEFINE(vkDestroyCommandPool)
VKF_FUNCTION_DEFINE(vkResetCommandPool)
VKF_FUNCTION_DEFINE(vkAllocateCommandBuffers)
VKF_FUNCTION_DEFINE(vkFreeCommandBuffers)
VKF_FUNCTION_DEFINE(vkBeginCommandBuffer)
VKF_FUNCTION_DEFINE(vkEndCommandBuffer)
VKF_FUNCTION_DEFINE(vkResetCommandBuffer)
VKF_FUNCTION_DEFINE(vkCmdBindPipeline)
VKF_FUNCTION_DEFINE(vkCmdSetViewport)
VKF_FUNCTION_DEFINE(vkCmdSetScissor)
VKF_FUNCTION_DEFINE(vkCmdSetLineWidth)
VKF_FUNCTION_DEFINE(vkCmdSetDepthBias)
VKF_FUNCTION_DEFINE(vkCmdSetBlendConstants)
VKF_FUNCTION_DEFINE(vkCmdSetDepthBounds)
VKF_FUNCTION_DEFINE(vkCmdSetStencilCompareMask)
VKF_FUNCTION_DEFINE(vkCmdSetStencilWriteMask)
VKF_FUNCTION_DEFINE(vkCmdSetStencilReference)
VKF_FUNCTION_DEFINE(vkCmdBindDescriptorSets)
VKF_FUNCTION_DEFINE(vkCmdBindIndexBuffer)
VKF_FUNCTION_DEFINE(vkCmdBindVertexBuffers)
VKF_FUNCTION_DEFINE(vkCmdDraw)
VKF_FUNCTION_DEFINE(vkCmdDrawIndexed)
VKF_FUNCTION_DEFINE(vkCmdDrawIndirect)
VKF_FUNCTION_DEFINE(vkCmdDrawIndexedIndirect)
VKF_FUNCTION_DEFINE(vkCmdDispatch)
VKF_FUNCTION_DEFINE(vkCmdDispatchIndirect)
VKF_FUNCTION_DEFINE(vkCmdCopyBuffer)
VKF_FUNCTION_DEFINE(vkCmdCopyImage)
VKF_FUNCTION_DEFINE(vkCmdBlitImage)
VKF_FUNCTION_DEFINE(vkCmdCopyBufferToImage)
VKF_FUNCTION_DEFINE(vkCmdCopyImageToBuffer)
VKF_FUNCTION_DEFINE(vkCmdUpdateBuffer)
VKF_FUNCTION_DEFINE(vkCmdFillBuffer)
VKF_FUNCTION_DEFINE(vkCmdClearColorImage)
VKF_FUNCTION_DEFINE(vkCmdClearDepthStencilImage)
VKF_FUNCTION_DEFINE(vkCmdClearAttachments)
VKF_FUNCTION_DEFINE(vkCmdResolveImage)
VKF_FUNCTION_DEFINE(vkCmdSetEvent)
VKF_FUNCTION_DEFINE(vkCmdResetEvent)
VKF_FUNCTION_DEFINE(vkCmdWaitEvents)
VKF_FUNCTION_DEFINE(vkCmdPipelineBarrier)
VKF_FUNCTION_DEFINE(vkCmdBeginQuery)
VKF_FUNCTION_DEFINE(vkCmdEndQuery)
VKF_FUNCTION_DEFINE(vkCmdResetQueryPool)
VKF_FUNCTION_DEFINE(vkCmdWriteTimestamp)
VKF_FUNCTION_DEFINE(vkCmdCopyQueryPoolResults)
VKF_FUNCTION_DEFINE(vkCmdPushConstants)
VKF_FUNCTION_DEFINE(vkCmdBeginRenderPass)
VKF_FUNCTION_DEFINE(vkCmdNextSubpass)
VKF_FUNCTION_DEFINE(vkCmdEndRenderPass)
VKF_FUNCTION_DEFINE(vkCmdExecuteCommands)
#endif

// -----------------------------------------------------------------------------
// Vulkan 1.1
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkEnumerateInstanceVersion)
VKF_FUNCTION_DEFINE(vkBindBufferMemory2)
VKF_FUNCTION_DEFINE(vkBindImageMemory2)
VKF_FUNCTION_DEFINE(vkGetDeviceGroupPeerMemoryFeatures)
VKF_FUNCTION_DEFINE(vkCmdSetDeviceMask)
VKF_FUNCTION_DEFINE(vkCmdDispatchBase)
VKF_FUNCTION_DEFINE(vkEnumeratePhysicalDeviceGroups)
VKF_FUNCTION_DEFINE(vkGetImageMemoryRequirements2)
VKF_FUNCTION_DEFINE(vkGetBufferMemoryRequirements2)
VKF_FUNCTION_DEFINE(vkGetImageSparseMemoryRequirements2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFeatures2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceProperties2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFormatProperties2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceImageFormatProperties2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceQueueFamilyProperties2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceMemoryProperties2)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSparseImageFormatProperties2)
VKF_FUNCTION_DEFINE(vkTrimCommandPool)
VKF_FUNCTION_DEFINE(vkGetDeviceQueue2)
VKF_FUNCTION_DEFINE(vkCreateSamplerYcbcrConversion)
VKF_FUNCTION_DEFINE(vkDestroySamplerYcbcrConversion)
VKF_FUNCTION_DEFINE(vkCreateDescriptorUpdateTemplate)
VKF_FUNCTION_DEFINE(vkDestroyDescriptorUpdateTemplate)
VKF_FUNCTION_DEFINE(vkUpdateDescriptorSetWithTemplate)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceExternalBufferProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceExternalFenceProperties)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceExternalSemaphoreProperties)
VKF_FUNCTION_DEFINE(vkGetDescriptorSetLayoutSupport)
#endif

// -----------------------------------------------------------------------------
// KHR Swapchain
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkCreateSwapchainKHR)
VKF_FUNCTION_DEFINE(vkDestroySwapchainKHR)
VKF_FUNCTION_DEFINE(vkGetSwapchainImagesKHR)
VKF_FUNCTION_DEFINE(vkAcquireNextImageKHR)
VKF_FUNCTION_DEFINE(vkQueuePresentKHR)
VKF_FUNCTION_DEFINE(vkGetDeviceGroupPresentCapabilitiesKHR)
VKF_FUNCTION_DEFINE(vkGetDeviceGroupSurfacePresentModesKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDevicePresentRectanglesKHR)
VKF_FUNCTION_DEFINE(vkAcquireNextImage2KHR)
#endif

// -----------------------------------------------------------------------------
// KHR Surface
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkDestroySurfaceKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSurfaceSupportKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSurfaceFormatsKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSurfacePresentModesKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Display
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceDisplayPropertiesKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceDisplayPlanePropertiesKHR)
VKF_FUNCTION_DEFINE(vkGetDisplayPlaneSupportedDisplaysKHR)
VKF_FUNCTION_DEFINE(vkGetDisplayModePropertiesKHR)
VKF_FUNCTION_DEFINE(vkCreateDisplayModeKHR)
VKF_FUNCTION_DEFINE(vkGetDisplayPlaneCapabilitiesKHR)
VKF_FUNCTION_DEFINE(vkCreateDisplayPlaneSurfaceKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Display Swapchain
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkCreateSharedSwapchainsKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Multiview
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFeatures2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceProperties2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceFormatProperties2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceImageFormatProperties2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceQueueFamilyProperties2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceMemoryProperties2KHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceSparseImageFormatProperties2KHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xcb Surface
//
#if defined(VK_USE_PLATFORM_XCB_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateXcbSurfaceKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceXcbPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xlib Surface
//
#if defined(VK_USE_PLATFORM_XLIB_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateXlibSurfaceKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceXlibPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Win32 Surface
//
#if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateWin32SurfaceKHR)
VKF_FUNCTION_DEFINE(vkGetPhysicalDeviceWin32PresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Android Surface
//
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateAndroidSurfaceKHR)
#endif

// -----------------------------------------------------------------------------
// KHR MacOS Surface
//
#if defined(VK_USE_PLATFORM_MACOS_MVK) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateMacOSSurfaceMVK)
#endif

// -----------------------------------------------------------------------------
// KHR IOS Surface
//
#if defined(VK_USE_PLATFORM_IOS_MVK) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_DEFINE(vkCreateIOSSurfaceMVK)
#endif

static void* sharedLibrary = NULL;

bool loadVulkanLibrary() {
#ifdef __linux__
	sharedLibrary = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
	if(sharedLibrary == NULL) {
		return false;
	}
#elif defined(WIN32)
	sharedLibrary = LoadLibraryA("vulkan-1.dll");
	if(sharedLibrary == NULL) {
		return false;
	}
#endif
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetInstanceProcAddr)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetInstanceProcAddr)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateInstance)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyInstance)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumeratePhysicalDevices)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceFormatProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumerateInstanceExtensionProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumerateInstanceLayerProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumerateDeviceLayerProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumerateDeviceExtensionProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceQueueFamilyProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceFeatures)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceMemoryProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceImageFormatProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateDevice)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyDevice)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDeviceWaitIdle)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateCommandPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkResetCommandPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyCommandPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkAllocateCommandBuffers)
	VKF_FUNCTION_LOAD(sharedLibrary, vkBeginCommandBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEndCommandBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkFreeCommandBuffers)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateSemaphore)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySemaphore)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateFence)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyFence)
	VKF_FUNCTION_LOAD(sharedLibrary, vkResetFences)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetFenceStatus)
	VKF_FUNCTION_LOAD(sharedLibrary, vkWaitForFences)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateEvent)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdPipelineBarrier)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceQueue)
	VKF_FUNCTION_LOAD(sharedLibrary, vkQueueSubmit)
	VKF_FUNCTION_LOAD(sharedLibrary, vkQueueWaitIdle)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySurfaceKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBeginRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdEndRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceProcAddr)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateImageView)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateFramebuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetImageMemoryRequirements)
	VKF_FUNCTION_LOAD(sharedLibrary, vkAllocateMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkBindImageMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyFramebuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyImageView)
	VKF_FUNCTION_LOAD(sharedLibrary, vkFreeMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetBufferMemoryRequirements)
	VKF_FUNCTION_LOAD(sharedLibrary, vkBindBufferMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkMapMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkUnmapMemory)
	VKF_FUNCTION_LOAD(sharedLibrary, vkFlushMappedMemoryRanges)
	VKF_FUNCTION_LOAD(sharedLibrary, vkInvalidateMappedMemoryRanges)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceMemoryCommitment)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetImageSparseMemoryRequirements)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSparseImageFormatProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkQueueBindSparse)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateDescriptorSetLayout)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyDescriptorSetLayout)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateDescriptorPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyDescriptorPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkAllocateDescriptorSets)
	VKF_FUNCTION_LOAD(sharedLibrary, vkUpdateDescriptorSets)
	VKF_FUNCTION_LOAD(sharedLibrary, vkFreeDescriptorSets)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreatePipelineCache)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyPipelineCache)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateShaderModule)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyShaderModule)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetImageSubresourceLayout)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateSampler)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySampler)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreatePipelineLayout)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateGraphicsPipelines)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyPipelineLayout)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyPipeline)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyBufferToImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdSetViewport)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdSetScissor)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBindPipeline)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBindVertexBuffers)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBindDescriptorSets)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBindIndexBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDrawIndexed)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDraw)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyEvent)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetEventStatus)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDrawIndirect)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDrawIndexedIndirect)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDispatch)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDispatchIndirect)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBlitImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyBufferToImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyImageToBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdUpdateBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdFillBuffer)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdClearColorImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdClearDepthStencilImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdClearAttachments)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdResolveImage)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdSetEvent)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdResetEvent)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdWaitEvents)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdPipelineBarrier)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBeginQuery)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdEndQuery)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdResetQueryPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdWriteTimestamp)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdCopyQueryPoolResults)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdPushConstants)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdBeginRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdNextSubpass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdEndRenderPass)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdExecuteCommands)

// -----------------------------------------------------------------------------
// KHR Swapchain
//
#ifdef VK_NO_PROTOTYPES
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateSwapchainKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySwapchainKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetSwapchainImagesKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkAcquireNextImageKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkQueuePresentKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceGroupPresentCapabilitiesKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceGroupSurfacePresentModesKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDevicePresentRectanglesKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkAcquireNextImage2KHR)
#endif

// -----------------------------------------------------------------------------
// KHR Surface
//
#ifdef VK_NO_PROTOTYPES
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySurfaceKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSurfaceSupportKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSurfaceFormatsKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSurfacePresentModesKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xcb Surface
//
#if defined(VK_USE_PLATFORM_XCB_KHR) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateXcbSurfaceKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceXcbPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xlib Surface
//
#if defined(VK_USE_PLATFORM_XLIB_KHR) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateXlibSurfaceKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceXlibPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Win32 Surface
//
#if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateWin32SurfaceKHR)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceWin32PresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Android Surface
//
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateAndroidSurfaceKHR)
#endif

// -----------------------------------------------------------------------------
// KHR MacOS Surface
//
#if defined(VK_USE_PLATFORM_MACOS_MVK) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateMacOSSurfaceMVK)
#endif

// -----------------------------------------------------------------------------
// KHR IOS Surface
//
#if defined(VK_USE_PLATFORM_IOS_MVK) && defined(VK_NO_PROTOTYPES)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateIOSSurfaceMVK)
#endif


// -----------------------------------------------------------------------------
// Vulkan 1.1
//
#ifdef VK_NO_PROTOTYPES
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumerateInstanceVersion)
	VKF_FUNCTION_LOAD(sharedLibrary, vkBindBufferMemory2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkBindImageMemory2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceGroupPeerMemoryFeatures)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdSetDeviceMask)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCmdDispatchBase)
	VKF_FUNCTION_LOAD(sharedLibrary, vkEnumeratePhysicalDeviceGroups)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetImageMemoryRequirements2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetBufferMemoryRequirements2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetImageSparseMemoryRequirements2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceFeatures2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceFormatProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceImageFormatProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceQueueFamilyProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceMemoryProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceSparseImageFormatProperties2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkTrimCommandPool)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDeviceQueue2)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateSamplerYcbcrConversion)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroySamplerYcbcrConversion)
	VKF_FUNCTION_LOAD(sharedLibrary, vkCreateDescriptorUpdateTemplate)
	VKF_FUNCTION_LOAD(sharedLibrary, vkDestroyDescriptorUpdateTemplate)
	VKF_FUNCTION_LOAD(sharedLibrary, vkUpdateDescriptorSetWithTemplate)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceExternalBufferProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceExternalFenceProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetPhysicalDeviceExternalSemaphoreProperties)
	VKF_FUNCTION_LOAD(sharedLibrary, vkGetDescriptorSetLayoutSupport)
#endif

	return true;
}

void init() {
	loadVulkanLibrary();
}

void destroy() {
#ifdef __linux__
	if(NULL != sharedLibrary) {
		dlclose(sharedLibrary);
		sharedLibrary = NULL;
	}
#elif defined(WIN32)
	if(NULL != sharedLibrary) {
		FreeLibrary(static_cast<HMODULE>(sharedLibrary));
		sharedLibrary = NULL;
	}
#endif
}

namespace vkf {

	BufferStride BufferStride::Zero = BufferStride(0);
	BufferSize BufferSize::Zero = BufferSize(0);

	const char* vkVkPresentModeKHRToString(VkPresentModeKHR presentMode) {
		switch(presentMode) {
			case VK_PRESENT_MODE_IMMEDIATE_KHR:
				return "VK_PRESENT_MODE_IMMEDIATE_KHR";
			case VK_PRESENT_MODE_MAILBOX_KHR:
				return "VK_PRESENT_MODE_MAILBOX_KHR";
			case VK_PRESENT_MODE_FIFO_KHR:
				return "VK_PRESENT_MODE_FIFO_KHR";
			case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
				return "VK_PRESENT_MODE_FIFO_RELAXED_KHR";
			default:
				break;
		}
		return "VK_PRESENT_MODE_MAX_ENUM_KHR";
	}

	const char* vkVkPhysicalDeviceTypeToString(VkPhysicalDeviceType physicalDeviceType) {
		switch(physicalDeviceType) {
			case VK_PHYSICAL_DEVICE_TYPE_OTHER:
				return "VK_PHYSICAL_DEVICE_TYPE_OTHER";
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				return "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				return "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				return "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				return "VK_PHYSICAL_DEVICE_TYPE_CPU";
			default:
				break;
		}
		return "VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM";
	}

	const char* vkVkResultToString(VkResult result) {
		switch(result) {
			case VK_SUCCESS:
				return "VK_SUCCESS";
			case VK_NOT_READY:
				return "VK_NOT_READY";
			case VK_TIMEOUT:
				return "VK_TIMEOUT";
			case VK_EVENT_SET:
				return "VK_EVENT_SET";
			case VK_EVENT_RESET:
				return "VK_EVENT_RESET";
			case VK_INCOMPLETE:
				return "VK_INCOMPLETE";
			case VK_ERROR_OUT_OF_HOST_MEMORY:
				return "VK_ERROR_OUT_OF_HOST_MEMORY";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:
				return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			case VK_ERROR_INITIALIZATION_FAILED:
				return "VK_ERROR_INITIALIZATION_FAILED";
			case VK_ERROR_DEVICE_LOST:
				return "VK_ERROR_DEVICE_LOST";
			case VK_ERROR_MEMORY_MAP_FAILED:
				return "VK_ERROR_MEMORY_MAP_FAILED";
			case VK_ERROR_LAYER_NOT_PRESENT:
				return "VK_ERROR_LAYER_NOT_PRESENT";
			case VK_ERROR_EXTENSION_NOT_PRESENT:
				return "VK_ERROR_EXTENSION_NOT_PRESENT";
			case VK_ERROR_FEATURE_NOT_PRESENT:
				return "VK_ERROR_FEATURE_NOT_PRESENT";
			case VK_ERROR_INCOMPATIBLE_DRIVER:
				return "VK_ERROR_INCOMPATIBLE_DRIVER";
			case VK_ERROR_TOO_MANY_OBJECTS:
				return "VK_ERROR_TOO_MANY_OBJECTS";
			case VK_ERROR_FORMAT_NOT_SUPPORTED:
				return "VK_ERROR_FORMAT_NOT_SUPPORTED";
			case VK_ERROR_SURFACE_LOST_KHR:
				return "VK_ERROR_SURFACE_LOST_KHR";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
				return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			case VK_SUBOPTIMAL_KHR:
				return "VK_SUBOPTIMAL_KHR";
			case VK_ERROR_OUT_OF_DATE_KHR:
				return "VK_ERROR_OUT_OF_DATE_KHR";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
				return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			case VK_ERROR_VALIDATION_FAILED_EXT:
				return "VK_ERROR_VALIDATION_FAILED_EXT";
			case VK_RESULT_RANGE_SIZE:
				return "VK_RESULT_RANGE_SIZE";
			default:
				break;
		}
		return "VK_RESULT_MAX_ENUM";
	}

	void init() {
		::loadVulkanLibrary();
	}

	void destroy() {
		::destroy();
	}

	VkResult showSupportedLayersAndExtensions() {
		//
		// Let's check the supported instance extensions.
		//
		uint32_t propertyCount = 0;
		VkResult result = vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, NULL);
		if(VK_SUCCESS != result) {
			std::cerr << "vkEnumerateInstanceExtensionProperties failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		std::vector<VkExtensionProperties> extensionProperties(propertyCount);
		vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, extensionProperties.data());
		std::cout << "Supported extension: " << std::endl;
		for(auto extension : extensionProperties) {
			std::cout << "Extension name: " << extension.extensionName << " Version: " << extension.specVersion << std::endl;
		}
		std::cout << std::endl;

		//
		// Let's check the supported instance layers.
		//
		uint32_t layerPropertyCount = 0;
		result = vkEnumerateInstanceLayerProperties(&layerPropertyCount, NULL);
		if(VK_SUCCESS != result) {
			std::cerr << "vkEnumerateInstanceLayerProperties failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		std::vector<VkLayerProperties> instanceLayerProperties(layerPropertyCount);
		vkEnumerateInstanceLayerProperties(&layerPropertyCount, instanceLayerProperties.data());
		std::cout << "Supported layer names: " << std::endl;
		for(auto extension : instanceLayerProperties) {
			std::cout << "Layer name: " << extension.layerName << " Version: " << extension.specVersion << std::endl;
		}
		std::cout << std::endl;

		return VK_SUCCESS;
	}

	uint32_t getMemoryTypeIndex(VkPhysicalDeviceMemoryProperties deviceMemoryProperties, VkMemoryRequirements& memoryRequirements, VkFlags properties) {
		for(uint32_t i = 0; i < deviceMemoryProperties.memoryTypeCount; i++) {
			if((memoryRequirements.memoryTypeBits & 1) == 1) {
				if((deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
					return i;
				}
			}
			memoryRequirements.memoryTypeBits >>= 1;
		}
		return UINT32_MAX;
	}

	void setImageLayout(VkCommandBuffer cmdbuffer,
	                    VkImage image,
	                    VkImageAspectFlags aspectMask,
	                    VkImageLayout oldImageLayout,
	                    VkImageLayout newImageLayout) {
		// Create an image barrier object
		VkImageMemoryBarrier imageMemoryBarrier {};
		imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.oldLayout = oldImageLayout;
		imageMemoryBarrier.newLayout = newImageLayout;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange.aspectMask = aspectMask;
		imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
		imageMemoryBarrier.subresourceRange.levelCount = 1;
		imageMemoryBarrier.subresourceRange.layerCount = 1;

		// Source layouts (old)

		// Undefined layout
		// Only allowed as initial layout!
		// Make sure any writes to the image have been finished
		if(oldImageLayout == VK_IMAGE_LAYOUT_UNDEFINED) {
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
		}

		// Old layout is color attachment
		// Make sure any writes to the color buffer have been finished
		if(oldImageLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		}

		// Old layout is transfer source
		// Make sure any reads from the image have been finished
		if(oldImageLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		}

		// Old layout is shader read (sampler, input attachment)
		// Make sure any shader reads from the image have been finished
		if(oldImageLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		}

		// Target layouts (new)

		// New layout is transfer destination (copy, blit)
		// Make sure any copyies to the image have been finished
		if(newImageLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		}

		// New layout is transfer source (copy, blit)
		// Make sure any reads from and writes to the image have been finished
		if(newImageLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
			imageMemoryBarrier.srcAccessMask = imageMemoryBarrier.srcAccessMask | VK_ACCESS_TRANSFER_READ_BIT;
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		}

		// New layout is color attachment
		// Make sure any writes to the color buffer hav been finished
		if(newImageLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		}

		// New layout is depth attachment
		// Make sure any writes to depth/stencil buffer have been finished
		if(newImageLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
			imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		}

		// New layout is shader read (sampler, input attachment)
		// Make sure any writes to the image have been finished
		if(newImageLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		}

		// Put barrier on top
		VkPipelineStageFlags srcStageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		VkPipelineStageFlags destStageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

		// Put barrier inside setup command buffer
		vkCmdPipelineBarrier(cmdbuffer, srcStageFlags, destStageFlags, 0, 0, NULL, 0, NULL, 1, &imageMemoryBarrier);
	}


#if VKF_SURFACE_WIN32
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch(message) {
			case WM_SIZE:
			case WM_EXITSIZEMOVE:
				PostMessage(hWnd, WM_USER + 1, wParam, lParam);
				break;
			case WM_KEYDOWN:
			case WM_CLOSE:
				PostMessage(hWnd, WM_USER + 2, wParam, lParam);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
#endif

	Windows::Windows(const std::string& title, uint32_t width, uint32_t height)
		:
#ifdef VKF_SURFACE_XCB
		m_connection(NULL)
		, m_screen(0)
		, m_window(0)
		, m_kss(NULL)
		, m_reply(NULL)
		, m_atom_wm_delete_window(NULL)
		,
#elif defined(VKF_SURFACE_XLIB)
		m_display(NULL)
		, m_window(None)
		,
#elif defined(VKF_SURFACE_WIN32)
		m_instance(0)
		, m_handle(0)
		,
#endif
		m_title(title)
		, m_width(width)
		, m_height(height) {
	}

	Windows::~Windows() {
		destroy();
	}

	int Windows::init() {

#ifdef VKF_SURFACE_XCB
		//
		// Connect to X11 server and create a window.
		//
		m_connection = xcb_connect(NULL, NULL);
		m_screen = xcb_setup_roots_iterator(xcb_get_setup(m_connection)).data;
		m_window = xcb_generate_id(m_connection);

		uint32_t values[2];
		uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		values[0] = m_screen->black_pixel;
		values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
		            XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
		            XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;

		xcb_create_window(m_connection,    // X11 connection.
		                  XCB_COPY_FROM_PARENT,          // Depth.
		                  m_window,                      // Window id.
		                  m_screen->root,                // Parent window.
		                  0, 0,                          // X, Y position of the window on the screen.
		                  m_width, m_height,             // Width, Height of the window.
		                  0,                             // Border width.
		                  XCB_WINDOW_CLASS_INPUT_OUTPUT, // Class type. (Input/Output for normal window)
		                  m_screen->root_visual,         // Visual.
		                  mask,                          // Masks.
		                  values);                       // Values.

		m_cookie = xcb_intern_atom(m_connection, 1, 12, "WM_PROTOCOLS");
		m_reply = xcb_intern_atom_reply(m_connection, m_cookie, 0);

		m_cookie2 = xcb_intern_atom(m_connection, 0, 16, "WM_DELETE_WINDOW");
		m_atom_wm_delete_window = xcb_intern_atom_reply(m_connection, m_cookie2, 0);

		xcb_change_property(
		  m_connection, XCB_PROP_MODE_REPLACE, m_window, (*m_reply).atom, 4, 32, 1, &(*m_atom_wm_delete_window).atom);
		xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
		                    m_title.size(), m_title.c_str());

		free(m_reply);

		// Flush the command queue for the X11 server.
		xcb_flush(m_connection);

		// Create Key symbols which will be used when converting key events into keysym.
		m_kss = xcb_key_symbols_alloc(getConnection());
#elif defined(VKF_SURFACE_XLIB)
		m_display = XOpenDisplay(NULL);
		if(NULL == m_display) {
			std::cerr << "Couldn't connect to X11 display server." << std::endl;
			return 1;
		}

		m_window = XCreateSimpleWindow(m_display, DefaultRootWindow(m_display), 0, 0, m_width, m_height, 0, 0, 0x888888);
		if(None == m_window) {
			std::cerr << "Couldn't create a X11 window." << std::endl;
			return 1;
		}
		XSelectInput(m_display, m_window, PropertyChangeMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask |
		             KeyReleaseMask | PointerMotionMask | StructureNotifyMask);
		WM_DELETE_WINDOW = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
		WM_PROTOCOLS = XInternAtom(m_display, "WM_PROTOCOLS", False);
		XFlush(m_display);
#elif defined(VKF_SURFACE_WIN32)
		m_instance = GetModuleHandle(NULL);

		// Register window class
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_instance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = m_title.c_str();
		wcex.hIconSm = NULL;

		if(!RegisterClassEx(&wcex)) {
			return 1;
		}

		// Create window
		m_handle = CreateWindow(m_title.c_str(), m_title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, m_width, m_height, NULL,
		                        NULL, m_instance, NULL);
		if(!m_handle) {
			return 1;
		}
#endif

		return 0;
	}

#ifdef VKF_SURFACE_XCB
	int Windows::init(xcb_connection_t* connection, xcb_window_t window) {
		m_connection = connection;
		m_window = window;
		return 0;
	}
#elif defined(VKF_SURFACE_XLIB)
	int Windows::init(Display* display, Window window) {
		m_display = display;
		m_window = window;
		return 0;
	}
#elif defined(VKF_SURFACE_WIN32)
	int Windows::init(HINSTANCE instance, HWND hwnd) {
		m_instance = instance;
		m_handle = hwnd;
		return 0;
	}
#endif

	int Windows::destroy() {
#ifdef VKF_SURFACE_XCB
		if(NULL != m_connection) {
			xcb_key_symbols_free(m_kss);
			xcb_destroy_window(m_connection, m_window);
			xcb_disconnect(m_connection);
		}
#elif defined(VKF_SURFACE_XLIB)
		if(None != m_window) {
			XUnmapWindow(m_display, m_window);
			XDestroyWindow(m_display, m_window);
			m_window = None;
		}
		if(NULL != m_display) {
			XCloseDisplay(m_display);
			m_display = NULL;
		}
#elif defined(VKF_SURFACE_WIN32)
		if(m_handle) {
			DestroyWindow(m_handle);
		}

		if(m_instance) {
			UnregisterClass(m_title.c_str(), m_instance);
		}
#endif
		return 0;
	}

	void Windows::setInputFocus() {
#ifdef VKF_SURFACE_XCB
		xcb_set_input_focus(m_connection, XCB_INPUT_FOCUS_POINTER_ROOT, m_window, XCB_CURRENT_TIME);
		xcb_flush(m_connection);
#elif defined(VKF_SURFACE_XLIB)
		XSetInputFocus(m_display, m_window, RevertToPointerRoot, CurrentTime);
		XFlush(m_display);
#endif
	}

	void Windows::show() {
#ifdef VKF_SURFACE_XCB
		xcb_map_window(m_connection, m_window);
		xcb_flush(m_connection);
#elif defined(VKF_SURFACE_XLIB)
		XMapRaised(m_display, m_window);
		XFlush(m_display);
#elif defined(VKF_SURFACE_WIN32)
		ShowWindow(m_handle, TRUE);
#endif
	}

	bool Windows::pollEvents() {
#ifdef VKF_SURFACE_WIN32
		MSG message;
		bool resize = false;

		if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			// Process events
			switch(message.message) {
				// Resize
				case WM_USER + 1:
					resize = true;
					break;
					return false;
				case WM_USER + 2:
					// loop = false;
					break;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		} else {
			// Draw
			//			if( resize ) {
			//				resize = false;
			//				if( !tutorial.OnWindowSizeChanged() ) {
			//					loop = false;
			//				}
			//			}
			//			if( !tutorial.Draw() ) {
			//				loop = false;
			//			}
		}
#elif defined(VKF_SURFACE_XCB)
		xcb_generic_event_t* event;
		event = xcb_poll_for_event(getConnection());
		if(NULL != event) {
			switch(event->response_type & ~0x80) {

				case XCB_EXPOSE: {
					//							xcb_expose_event_t *ev = (xcb_expose_event_t *)event;
					break;
				}

				case XCB_KEY_PRESS: {
					xcb_key_press_event_t* ev = (xcb_key_press_event_t*)event;
					xcb_keysym_t ks = xcb_key_symbols_get_keysym(m_kss, ev->detail, 0);

					if(XK_Escape == ks) {
						return false;
					}

					break;
				}
				case XCB_KEY_RELEASE: {
					//							xcb_key_release_event_t* ev =
					//(xcb_key_release_event_t*)event;
					break;
				}
				case XCB_CLIENT_MESSAGE: {
					if((*(xcb_client_message_event_t*)event).data.data32[0] == (*m_atom_wm_delete_window).atom) {
						return false;
					}
				}
				break;

				case XCB_DESTROY_NOTIFY: {
					return false;
				}
				break;
			}
		}
#elif defined(VKF_SURFACE_XLIB)
		while(XPending(m_display)) {
			XEvent event;
			XNextEvent(m_display, &event);
			switch(event.type) {
				case ButtonPress: {
				} break;
				case ButtonRelease: {
				} break;
				case MotionNotify: {
				} break;
				case ClientMessage: {
					if((event.xclient.message_type == WM_PROTOCOLS) && ((Atom)event.xclient.data.l[0] == WM_DELETE_WINDOW) &&
					    (event.xclient.format == 32)) {
						return false;
					}
				}
				break;
				case KeyPress: {
					KeySym keysym = XkbKeycodeToKeysym(m_display, event.xkey.keycode, 0, 0);
					if(XK_Escape == keysym) {
						return false;
					}
				}
				break;
				case KeyRelease: {

				} break;
			}
		}
#endif

		return true;
	}

	uint32_t Windows::getWidth() const {
		return m_width;
	}

	uint32_t Windows::getHeight() const {
		return m_height;
	}

	const std::string& Windows::getTitle() const {
		return m_title;
	}

#ifdef VKF_SURFACE_XCB
	xcb_connection_t* Windows::getConnection() const {
		return m_connection;
	}

	xcb_window_t Windows::getWindow() const {
		return m_window;
	}
#elif defined(VKF_SURFACE_XLIB)

	Display* Windows::getDisplay() const {
		return m_display;
	}

	Window Windows::getWindow() const {
		return m_window;
	}
#elif defined(VKF_SURFACE_WIN32)

	HINSTANCE Windows::getInstance() const {
		return m_instance;
	}

	HWND Windows::getHandle() const {
		return m_handle;
	}
#endif

//
//
//

	Debug::Debug(VkInstance instance)
		: m_instance(instance)
		, m_callback(VK_NULL_HANDLE)
		, vkCreateDebugReportCallbackEXT(NULL)
		, vkDebugReportMessageEXT(NULL)
		, vkDestroyDebugReportCallbackEXT(NULL) {

		GET_INSTANCE_PROC_ADDR(m_instance, CreateDebugReportCallbackEXT);
		GET_INSTANCE_PROC_ADDR(m_instance, DebugReportMessageEXT);
		GET_INSTANCE_PROC_ADDR(m_instance, DestroyDebugReportCallbackEXT);
	}

	Debug::~Debug() {

		if(VK_NULL_HANDLE != m_callback) {
			vkDestroyDebugReportCallbackEXT(m_instance, m_callback, NULL);
			m_callback = VK_NULL_HANDLE;
		}
	}

	VkResult Debug::init() {
		VkDebugReportCallbackCreateInfoEXT callbackCreateInfo {};
		callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
		                           VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
		callbackCreateInfo.pfnCallback = &myDebugReportCallback;

		VkResult result = vkCreateDebugReportCallbackEXT(m_instance, &callbackCreateInfo, NULL, &m_callback);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDebugReportCallbackEXT failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}
		return result;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL Debug::myDebugReportCallback(VkDebugReportFlagsEXT flags,
	    VkDebugReportObjectTypeEXT objectType,
	    uint64_t object,
	    size_t location,
	    int32_t messageCode,
	    const char* pLayerPrefix,
	    const char* pMessage,
	    void* pUserData) {
		return VK_FALSE;
	}

//
//
//

	Instance::Instance(const std::string& title, uint32_t version)
		: m_instance(VK_NULL_HANDLE)
		, m_title(title)
		, m_version(version)
		, m_debug(NULL) {

	}

	Instance::~Instance() {

	}

	VkResult Instance::init() {

		//
		// Let's create the Vulkan applications info. We will use it for the VKInstanceCreateInfo.
		//
		const VkApplicationInfo applicationInfo {
			VK_STRUCTURE_TYPE_APPLICATION_INFO,
			NULL,
			m_title.c_str(),
			0,
			NULL,
			0,
			m_version
		};

		// Let's prepare the extension stuff. We will use the surface extension to handle native windows.
		const std::vector<const char*> enabledExtensions = {
			VK_KHR_SURFACE_EXTENSION_NAME,
#if defined(_WIN32)
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#elif defined(__ANDROID__)
			VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#elif defined(VKF_SURFACE_XCB)
			VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#elif defined(VKF_SURFACE_XLIB)
			VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#elif defined(VKF_SURFACE_WAYLAND)
			VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#elif defined(VKF_SURFACE_MIR)
			VK_KHR_MIR_SURFACE_EXTENSION_NAME,
#else
//#error "Vulkan Surface Platform not supported."
#endif
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME
		};

		const std::vector<const char*> layerExtensions = {
//			"VK_LAYER_GOOGLE_threading",
//			"VK_LAYER_LUNARG_parameter_validation",
//			"VK_LAYER_LUNARG_core_validation",
//			"VK_LAYER_LUNARG_swapchain",
		};

		//
		// Let's create the Vulkan instance info which is mandatory.
		//

		const VkInstanceCreateInfo instanceCreateInfo {
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			NULL,
			0,
			&applicationInfo,
			(uint32_t)layerExtensions.size(),
			layerExtensions.data(),
			(uint32_t)enabledExtensions.size(),
			enabledExtensions.data()
		};

		//
		// Create the Vulkan instance.
		//
		VkResult result = vkCreateInstance(&instanceCreateInfo, NULL, &m_instance);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateInstance failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		return postInit();
	}

	VkResult Instance::init(VkInstance instance) {
		m_instance = instance;
		return postInit();
	}

	void Instance::destroy() {
		if(NULL != m_debug) {
			delete m_debug;
		}
		if(VK_NULL_HANDLE != m_instance) {
			vkDestroyInstance(m_instance, NULL);
			m_instance = VK_NULL_HANDLE;
		}
	}

	VkResult Instance::postInit() {
		m_debug = new Debug(m_instance);
		VkResult result = m_debug->init();
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateInstance failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// -------------------------------------------------------------------------
		// Get all infos about available devices.
		//
		uint32_t deviceCount;
		result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, NULL);
		if(result != VK_SUCCESS) {
			std::cerr << "vkEnumeratePhysicalDevices failed: " << vkf::vkVkResultToString(result) << std::endl;
			exit(1);
		}

		m_physicalDevices.reserve(deviceCount);
		m_physicalDevices.resize(deviceCount);
		result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, m_physicalDevices.data());
		if(result != VK_SUCCESS) {
			std::cerr << "vkEnumeratePhysicalDevices failed: " << vkf::vkVkResultToString(result) << std::endl;
			exit(1);
		}
		return result;
	}

	const std::vector<VkPhysicalDevice>& Instance::getPhysicalDevices() const {
		return m_physicalDevices;
	}

//
//
//

	Device::Device(Instance* instance, VkPhysicalDeviceType physicalDeviceType)
		: m_instance(instance)
		, m_physicalDevice(VK_NULL_HANDLE)
		, m_device(VK_NULL_HANDLE)
		, m_physicalDeviceType(physicalDeviceType)
		, m_deviceProperties {}
		, m_deviceFeatures {}
		, m_graphicsQueueIndex(UINT32_MAX)
		, m_maxGraphicsQueueCount(UINT32_MAX)
		, m_queueIndex(0)
		, m_physicalDeviceMemoryProperties {} {
	}

	Device::~Device() {
	}

	VkResult Device::preInit() {
		if(m_instance->getPhysicalDevices().size() == 0) {
			std::cerr << "Instance object has no physical devices." << std::endl;
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		//
		// Get the physical device the user specified. Default is VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU.
		//
		for(auto device : m_instance->getPhysicalDevices()) {
			vkGetPhysicalDeviceProperties(device, &m_deviceProperties);

			std::cout << "Device         : " << m_deviceProperties.deviceName << " > "
			          << vkVkPhysicalDeviceTypeToString(m_deviceProperties.deviceType) << std::endl;
			std::cout << "Driver Version : " << m_deviceProperties.driverVersion << std::endl;

			if(m_deviceProperties.deviceType == m_physicalDeviceType) {
				m_physicalDevice = device;
				break;
			}
		}

		// Did we find the Physical Device the user specified?
		if(VK_NULL_HANDLE == m_physicalDevice) {
			std::cerr << "Couldn't find specified device type." << std::endl;
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, NULL);

		m_queueFamilyProperties.reserve(queueFamilyCount);
		m_queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, m_queueFamilyProperties.data());

		// Get the index for the graphics queue.
		// TODO We have to change this later if the user wants to use the physical device other than as GFX device.
		for(uint32_t j = 0; j < queueFamilyCount; j++) {
			if((m_queueFamilyProperties[j].queueCount > 0) && (m_queueFamilyProperties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
				std::cout << "VK_QUEUE_GRAPHCIS_BIT found for physical device with "
				          << m_queueFamilyProperties[j].queueCount << " supported queues." << std::endl;
				m_graphicsQueueIndex = j;
				m_maxGraphicsQueueCount = m_queueFamilyProperties[j].queueCount;
			}
		}
		if(UINT32_MAX == m_graphicsQueueIndex) {
			std::cout << "Couldn't find graphics queue index." << std::endl;
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_physicalDeviceMemoryProperties);
		std::cout << "Memory Type Count: " << m_physicalDeviceMemoryProperties.memoryTypeCount << std::endl;
		std::cout << "Memory Heap Count: " << m_physicalDeviceMemoryProperties.memoryHeapCount << std::endl;

		return VK_SUCCESS;
	}

	VkResult Device::init() {

		VkResult result = preInit();
		if(VK_SUCCESS != result) {
			return result;
		}

		//
		// Next step is to create the queue. For this we have to create first the info for it.
		//
		VkDeviceQueueCreateInfo deviceQueueInfo {};
		deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueInfo.queueFamilyIndex = m_graphicsQueueIndex;
		deviceQueueInfo.queueCount = m_maxGraphicsQueueCount;
		float queuePriorities[] = { 0.0f };
		deviceQueueInfo.pQueuePriorities = queuePriorities;

		//
		// Here we will create the real physical device connection. Because we are going to use
		// this device for rendering on the screen we need the SwapChain extension.
		//
		std::vector<const char*> enabledExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		VkDeviceCreateInfo deviceCreateInfo {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		if(enabledExtensions.size() > 0) {
			deviceCreateInfo.enabledExtensionCount = (uint32_t)enabledExtensions.size();
			deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();
		}

		deviceCreateInfo.queueCreateInfoCount = 1;
		deviceCreateInfo.pQueueCreateInfos = &deviceQueueInfo;

		result = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, NULL, &m_device);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDevice failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		return VK_SUCCESS;
	}

	VkResult Device::init(VkDevice device) {
		m_device = device;

		return preInit();
	}

	void Device::destroy() {
		if(VK_NULL_HANDLE != m_device) {
			vkDestroyDevice(m_device, NULL);
			m_device = VK_NULL_HANDLE;
		}
	}

	Instance* Device::getInstance() const {
		return m_instance;
	}

	VkResult Device::waitIdle() {
		VkResult result = vkDeviceWaitIdle(m_device);
		if(VK_SUCCESS != result) {
			std::cerr << "vkDeviceWaitIdle failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	VkPhysicalDeviceMemoryProperties Device::getPhysicalDeviceMemoryProperties() const {
		return m_physicalDeviceMemoryProperties;
	}

	const std::vector<VkQueueFamilyProperties>& Device::getQueueFamilyProperties() const {
		return m_queueFamilyProperties;
	}

	VkPhysicalDevice Device::getPhysicalDevice() const {
		return m_physicalDevice;
	}

	uint32_t Device::getGraphicsQueueIndex() const {
		return m_graphicsQueueIndex;
	}

	uint32_t Device::getQueueIndex() const {
		return m_queueIndex;
	}

//
//
//

	CommandPool::CommandPool(Device* device, VkCommandPoolCreateFlags commandPoolCreateFlags)
		: m_device(device)
		, m_cmdPool(VK_NULL_HANDLE)
		, m_commandPoolCreateFlags(commandPoolCreateFlags) {
	}

	CommandPool::~CommandPool() {
	}

	VkResult CommandPool::init() {

		VkCommandPoolCreateInfo cmdPoolInfo {};
		cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolInfo.queueFamilyIndex = m_device->getGraphicsQueueIndex();
		cmdPoolInfo.flags = m_commandPoolCreateFlags;

		VkResult result = vkCreateCommandPool(*m_device, &cmdPoolInfo, NULL, &m_cmdPool);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateCommandPool failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		return result;
	}

	VkResult CommandPool::reset(VkCommandPoolCreateFlags commandPoolCreateFlags) {
		m_commandPoolCreateFlags = commandPoolCreateFlags;

		VkResult result = vkResetCommandPool(*m_device, m_cmdPool, m_commandPoolCreateFlags);
		if(VK_SUCCESS != result) {
			std::cerr << "vkResetCommandPool failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		return result;
	}

	Device& CommandPool::getDevice() const {
		return *m_device;
	}

	void CommandPool::destroy() {
		if(VK_NULL_HANDLE != m_cmdPool) {
			vkDestroyCommandPool(*m_device, m_cmdPool, NULL);
			m_cmdPool = VK_NULL_HANDLE;
		}
	}

//
//
//

	CommandBuffer::CommandBuffer(CommandPool* commandPool)
		: m_commandPool(commandPool)
		, m_cmdBuffer(VK_NULL_HANDLE)
		, m_isBegin(false) {
	}

	CommandBuffer::~CommandBuffer() {
	}

	VkResult CommandBuffer::init() {

		VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = *m_commandPool;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandBufferCount = 1;

		VkResult result = vkAllocateCommandBuffers(m_commandPool->getDevice(), &commandBufferAllocateInfo, &m_cmdBuffer);
		if(result != VK_SUCCESS) {
			std::cerr << "vkAllocateCommandBuffers failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}
		return result;
	}

	VkResult CommandBuffer::begin() {
		assert(true != m_isBegin && "vkBeginCommandBuffer will fail because it is already used.");

		VkCommandBufferBeginInfo commandBufferBeginInfo {};
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		// Command buffer will be reset and recorded again between each submission.
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VkResult result = vkBeginCommandBuffer(m_cmdBuffer, &commandBufferBeginInfo);
		if(result != VK_SUCCESS) {
			std::cerr << "vkBeginCommandBuffer failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		m_isBegin = true;

		return result;
	}

	VkResult CommandBuffer::end() {
		assert(true == m_isBegin && "vkEndCommandBuffer will fail because vkBeginCommandBuffer is not used.");

		VkResult result = vkEndCommandBuffer(m_cmdBuffer);
		if(result != VK_SUCCESS) {
			std::cerr << "vkEndCommandBuffer failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		m_isBegin = false;

		return result;
	}

	void CommandBuffer::destroy() {
		if(VK_NULL_HANDLE != m_cmdBuffer) {
			vkFreeCommandBuffers(m_commandPool->getDevice(), *m_commandPool, 1, &m_cmdBuffer);
			m_cmdBuffer = VK_NULL_HANDLE;
		}
		m_isBegin = false;
	}

	void CommandBuffer::reset() {
		vkResetCommandPool(m_commandPool->getDevice(), *m_commandPool, 0);
	}

//
//
//

	CommandBuffers::CommandBuffers(Device* device, CommandPool* commandPool, uint32_t number)
		: m_device(device)
		, m_commandPool(commandPool)
		, m_postPresentCmdBuffer(VK_NULL_HANDLE) {
		m_cmdBuffers.reserve(number);
		m_cmdBuffers.resize(number);
	}

	CommandBuffers::~CommandBuffers() {
	}

	VkResult CommandBuffers::init() {

		for(size_t index = 0; index < m_cmdBuffers.size(); index++) {
			m_cmdBuffers[index] = new CommandBuffer(m_commandPool);
			VkResult Result = m_cmdBuffers[index]->init();
			if(VK_SUCCESS != Result) {
				destroy();
				return Result;
			}
		}

		return VK_SUCCESS;
	}

	void CommandBuffers::destroy() {
		for(auto& commandBuffer : m_cmdBuffers) {
			commandBuffer->destroy();
		}
		m_cmdBuffers.clear();
	}

	const std::vector<CommandBuffer*>& CommandBuffers::getCommandBuffers() const {
		return m_cmdBuffers;
	}

//
//
//

	Semaphore::Semaphore(Device* device)
		: m_device(device)
		, m_semaphore(VK_NULL_HANDLE) {
	}

	Semaphore::~Semaphore() {
	}

	VkResult Semaphore::init() {
		VkSemaphoreCreateInfo semaphoreCreateInfo {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkResult result = vkCreateSemaphore(*m_device, &semaphoreCreateInfo, NULL, &m_semaphore);
		if(result != VK_SUCCESS) {
			std::cerr << "vkCreateSemaphore failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void Semaphore::destroy() {
		if(VK_NULL_HANDLE != m_semaphore) {
			vkDestroySemaphore(*m_device, m_semaphore, NULL);
			m_semaphore = VK_NULL_HANDLE;
		}
	}

//
//
//

	Fence::Fence(Device* device)
		: m_device(device)
		, m_fence(VK_NULL_HANDLE) {
	}

	VkResult Fence::init() {
		VkFenceCreateInfo fenceCreateInfo {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		VkResult result = vkCreateFence(*m_device, &fenceCreateInfo, NULL, &m_fence);
		if(VK_SUCCESS != result) {
			std::cerr << "vkQueueSubmit failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void Fence::destroy() {
		if(VK_NULL_HANDLE == m_fence) {
			vkDestroyFence(*m_device, m_fence, NULL);
			m_fence = VK_NULL_HANDLE;
		}
	}

	void Fence::reset() {
		vkResetFences(*m_device, 1, &m_fence);
	}

//
//
//

	FenceManager::FenceManager(Device* device)
		: m_device(device) {
	}

	VkResult FenceManager::init() {
		return VK_SUCCESS;
	}

	void FenceManager::destroy() {
		for(auto& fence : m_fences) {
			fence.destroy();
		}
		m_fences.clear();
	}

	VkResult FenceManager::getStatus(Fence& fence) {
		return vkGetFenceStatus(*m_device, fence);
	}

	VkResult FenceManager::add(Fence& fence) {
		VkResult result = fence.init();
		if(VK_SUCCESS != result) {
			std::cerr << "Couldn't add fence to manager because initialization failed." << std::endl;
			return result;
		}
		m_fences.push_back(fence);
		return result;
	}

	void FenceManager::remove(Fence& fence) {
//		for(auto& fence : m_fences) {
//			m_fences.erase(fence);
//		}
	}

	void FenceManager::reset(Fence& fence) {
		vkResetFences(*m_device, 1, fence);
	}

	void FenceManager::resetAll() {
		vkResetFences(*m_device, m_fences.size(), *m_fences.data());
	}

	VkResult FenceManager::waitForAllFences() {
		VkResult result = vkWaitForFences(*m_device, m_fences.size(), *m_fences.data(), VK_TRUE, 0);

		assert(result != VK_ERROR_DEVICE_LOST);
		return result;
	}

//
//
//

	Queue::Queue(Device* device, uint32_t famliyQueueIndex, uint32_t queueIndex)
		: m_device(device)
		, m_queue(VK_NULL_HANDLE)
		, m_queueFamilyIndex(famliyQueueIndex)
		, m_queueIndex(queueIndex) {
	}

	VkResult Queue::init() {
		vkGetDeviceQueue(*m_device, m_queueFamilyIndex, m_queueIndex, &m_queue);
		return VK_SUCCESS;
	}

	void Queue::destroy() {
	}

	VkResult Queue::submit(VkSubmitInfo& submitInfo) {
		VkResult result = vkQueueSubmit(m_queue, 1, &submitInfo, VK_NULL_HANDLE);
		if(VK_SUCCESS != result) {
			std::cerr << "vkQueueSubmit failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	VkResult Queue::submit(CommandBuffer* commandBuffer) {
		VkSubmitInfo submitInfo {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = *commandBuffer;

		VkResult result = vkQueueSubmit(m_queue, 1, &submitInfo, VK_NULL_HANDLE);
		if(VK_SUCCESS != result) {
			std::cerr << "vkQueueSubmit failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	VkResult Queue::submit(CommandBuffer* commandBuffer, const VkPipelineStageFlags pipelineStageFlags) {
		VkSubmitInfo submitInfo {};
		submitInfo.pWaitDstStageMask = &pipelineStageFlags;
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = *commandBuffer;

		VkResult result = vkQueueSubmit(m_queue, 1, &submitInfo, VK_NULL_HANDLE);
		if(VK_SUCCESS != result) {
			std::cerr << "vkQueueSubmit failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	VkResult Queue::submit(CommandBuffer* commandBuffer, VkPipelineStageFlags pipelineStageFlags, Semaphore* renderComplete, Semaphore* presentComplete) {
		VkSubmitInfo submitInfo {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pWaitDstStageMask = &pipelineStageFlags;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = *commandBuffer;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = *presentComplete;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = *renderComplete;
		VkResult result = vkQueueSubmit(m_queue, 1, &submitInfo, VK_NULL_HANDLE);
		if(VK_SUCCESS != result) {
			std::cerr << "vkQueueSubmit failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	VkResult Queue::waitIdle() {
		VkResult result = vkQueueWaitIdle(m_queue);
		return result;
	}

	uint32_t Queue::getQueueFamilyIndex() const {
		return m_queueFamilyIndex;
	}

//
//
//

	Surface::Surface(Device* device, Windows* window)
		: m_device(device)
		, m_window(window)
		, m_surface(VK_NULL_HANDLE)
		, m_surfCaps {}
		, m_presentModeCount(0)
		, m_presentMode(VK_PRESENT_MODE_IMMEDIATE_KHR)
		, m_queueFamilyIndex(0)
		, m_queueIndex(0) {
	}

	Surface::~Surface() {

	}

	VkResult Surface::init() {
		VkResult result = VK_RESULT_MAX_ENUM;
#ifdef _WIN32
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance = (HINSTANCE)m_window->getInstance();
		surfaceCreateInfo.hwnd = (HWND)m_window->getHandle();
		result = vkCreateWin32SurfaceKHR(*m_device->getInstance(), &surfaceCreateInfo, NULL, &m_surface);
#elif defined(__ANDROID__)
		VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo;
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.window = window;
		result = vkCreateAndroidSurfaceKHR(m_device.getInstance(), &surfaceCreateInfo, NULL, &m_surface);
#elif defined(VKF_SURFACE_XCB)
		VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = { VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR, NULL, 0, m_window->getConnection(), m_window->getWindow() };
		result = vkCreateXcbSurfaceKHR(*m_device->getInstance(), &surfaceCreateInfo, NULL, &m_surface);
#elif defined(VKF_SURFACE_XLIB)
		VkXlibSurfaceCreateInfoKHR surfaceCreateInfo = { VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, NULL, 0, m_window->getDisplay(), m_window->getWindow() };
		result = vkCreateXlibSurfaceKHR(*m_device->getInstance(), &surfaceCreateInfo, NULL, &m_surface);
#else
//#error "Vulkan Surface Platform not supported."
#endif
		if(VK_SUCCESS != result) {
			std::cerr << "Failed to create Vulkan surface: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// Search for a graphics and a present queue in the array of queue
		// families, try to find one that supports both
		uint32_t m_queueIndex = 0;
		for(uint32_t i = 0; i < m_device->getQueueFamilyProperties().size(); i++) {

			VkBool32 supported = VK_FALSE;

			VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(m_device->getPhysicalDevice(), i, m_surface, &supported);
			if(VK_SUCCESS != result) {
				std::cerr << "vkGetPhysicalDeviceSurfaceSupportKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
				exit(1);
			}

			if(supported && (m_device->getQueueFamilyProperties()[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (m_device->getQueueFamilyProperties()[i].queueCount > m_queueIndex)) {
				m_queueFamilyIndex = i;
			}
		}

		// Get list of supported surface formats
		uint32_t formatCount;
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->getPhysicalDevice(), m_surface, &formatCount, NULL);
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetPhysicalDeviceSurfaceFormatsKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->getPhysicalDevice(), m_surface, &formatCount, surfaceFormats.data());
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetPhysicalDeviceSurfaceFormatsKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
		// there is no preferered format, so we assume VK_FORMAT_B8G8R8A8_UNORM
		if((formatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)) {
			m_colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
		} else {
			// Always select the first available color format
			// If you need a specific format (e.g. SRGB) you'd need to
			// iterate over the list of available surface format and
			// check for it's presence
			m_colorFormat = surfaceFormats[0].format;
		}
		m_colorSpace = surfaceFormats[0].colorSpace;

		surfaceFormats.clear();

		// Get physical device surface properties and formats.
		result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_device->getPhysicalDevice(), m_surface, &m_surfCaps);
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetPhysicalDeviceSurfaceCapabilitiesKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		if(m_surfCaps.currentExtent.width != UINT32_MAX) {
			m_extent2D.width = m_surfCaps.currentExtent.width;
			m_extent2D.height = m_surfCaps.currentExtent.height;
		}

		//
		// Get the number of Present Modes. (That is how stuff are drawn like using VSYNC or not ...)
		//
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_device->getPhysicalDevice(), m_surface, &m_presentModeCount, NULL);
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetPhysicalDeviceSurfacePresentModesKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// Use the number of modes and create an array of modes.
		std::vector<VkPresentModeKHR> presentModes(m_presentModeCount);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_device->getPhysicalDevice(), m_surface, &m_presentModeCount, presentModes.data());
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetPhysicalDeviceSurfacePresentModesKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		//
		// Select the Present mode we prefer. (Which is VSYNC'ed). If not supported than the normal way.
		//
		m_presentMode = VK_PRESENT_MODE_FIFO_KHR;
		for(auto presentMode : presentModes) {
			std::cout << "Supported SwapChain Present Modes: " << vkVkPresentModeKHRToString(presentMode) << std::endl;

			// We will try to use the Present Mode that waits for VSYNC.
			if(presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				m_presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				break;
			}

			if((m_presentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)) {
				m_presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}

		return result;
	}

	void Surface::destroy() {
		if(VK_NULL_HANDLE != m_surface) {
			vkDestroySurfaceKHR(*m_device->getInstance(), m_surface, NULL);
			m_surface = VK_NULL_HANDLE;
		}
	}

	Device& Surface::getDevice() const {
		return *m_device;
	}

	uint32_t Surface::getQueueFamilyIndex() const {
		return m_queueFamilyIndex;
	}

	uint32_t Surface::getQueueIndex() const {
		return m_queueIndex;
	}

	VkSurfaceCapabilitiesKHR Surface::getSurfaceCaps() const {
		return m_surfCaps;
	}

	uint32_t Surface::getPresentModeCount() const {
		return m_presentModeCount;
	}

	VkFormat Surface::getColorFormat() const {
		return m_colorFormat;
	}

	VkColorSpaceKHR Surface::getColorSpace() const {
		return m_colorSpace;
	}

	VkExtent2D Surface::getExtent2D() const {
		return m_extent2D;
	}

	VkPresentModeKHR Surface::getPresentMode() const {
		return m_presentMode;
	}

//
//
//

	RenderPass::RenderPass(Device* device)
		: m_device(device)
		, m_renderPass(VK_NULL_HANDLE)
		, m_swapChainRenderPass(false) {

	}

	RenderPass::~RenderPass() {

	}

	void RenderPass::addColorAttachment(VkFormat format, VkImageLayout initialImageLayout, VkImageLayout finalImageLayout) {
		VkAttachmentDescription colorAttachment {};
		colorAttachment.format = format;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.initialLayout = initialImageLayout;
		colorAttachment.finalLayout = finalImageLayout;
		m_colorAttachments.push_back(colorAttachment);
	}

	void RenderPass::addDepthStencilAttachment(VkFormat format, VkImageLayout initialImageLayout) {
		VkAttachmentDescription depthAttachment {};
		depthAttachment.format = format;
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = initialImageLayout;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		m_depthStencilAttachment.push_back(depthAttachment);
	}

	VkResult RenderPass::init() {

		std::vector<VkAttachmentReference> colorAttachmentReferences;
		std::vector<VkAttachmentReference> depthStencilAttachmentReferences;
		size_t idx = 0;

		std::vector<VkAttachmentDescription> attachments;
		for(auto& color : m_colorAttachments) {
			VkAttachmentReference colorReference {};
			colorReference.attachment = idx++;
			colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			colorAttachmentReferences.push_back(colorReference);

			attachments.push_back(color);
		}

		for(auto& depthStencil : m_depthStencilAttachment) {
			VkAttachmentReference depthReference {};
			depthReference.attachment = idx;
			depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			depthStencilAttachmentReferences.push_back(depthReference);

			attachments.push_back(depthStencil);
		}

		std::vector<VkSubpassDescription> subpassDescriptions {};
		VkSubpassDescription subpassDescription {};
		subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescription.inputAttachmentCount = 0;
		subpassDescription.pInputAttachments = 0;
		subpassDescription.colorAttachmentCount = colorAttachmentReferences.size();
		subpassDescription.pColorAttachments = colorAttachmentReferences.data();
		subpassDescription.pDepthStencilAttachment = depthStencilAttachmentReferences.data();
		subpassDescriptions.push_back(subpassDescription);


		// Global render pass for frame buffer writes
		VkRenderPassCreateInfo renderPassCreateInfo {};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = attachments.size();
		renderPassCreateInfo.pAttachments = attachments.data();
		renderPassCreateInfo.subpassCount = subpassDescriptions.size();
		renderPassCreateInfo.pSubpasses = subpassDescriptions.data();

		VkResult result = vkCreateRenderPass(*m_device, &renderPassCreateInfo, NULL, &m_renderPass);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateRenderPass failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void RenderPass::destroy() {
		if(VK_NULL_HANDLE != m_renderPass) {
			vkDestroyRenderPass(*m_device, m_renderPass, NULL);
			m_renderPass = VK_NULL_HANDLE;
		}
	}

//
//
//

	RenderPassScope::RenderPassScope(CommandBuffer* commandBuffer, SwapChain* swapChain, uint32_t currentBuffer, std::array<VkClearValue, 2>& clearValues)
		: m_commandBuffer(commandBuffer) {

		VkRenderPassBeginInfo renderPassBeginInfo {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.framebuffer = swapChain->getFramebuffer(currentBuffer);
		renderPassBeginInfo.renderPass = swapChain->getRenderPass();
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent = swapChain->getSurface()->getExtent2D();
		renderPassBeginInfo.clearValueCount = clearValues.size();
		renderPassBeginInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(*m_commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	RenderPassScope::~RenderPassScope() {
		vkCmdEndRenderPass(*m_commandBuffer);
	}

//
//
//

	SwapChain::SwapChain(Surface* surface)
		: m_surface(surface)
		, m_renderPass(NULL)
		, m_swapChain(VK_NULL_HANDLE)
		, m_oldSwapchain(VK_NULL_HANDLE)
		, m_swapchainCreateInfo {}
		, m_depthStencilFormat(VK_FORMAT_D24_UNORM_S8_UINT)
		, m_depthStencilImage {}
		, m_fence(VK_NULL_HANDLE) {
	}

	SwapChain::~SwapChain() {

	}


	RenderPass& SwapChain::getRenderPass() const {
		return *m_renderPass;
	}

	VkResult SwapChain::init() {

		m_oldSwapchain = m_swapChain;

		// Determine the number of images. We want to use at least one.
		uint32_t numberImages = m_surface->getSurfaceCaps().minImageCount + 1;

		VkSurfaceTransformFlagsKHR preTransform {};
		if(m_surface->getSurfaceCaps().supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		} else {
			preTransform = m_surface->getSurfaceCaps().currentTransform;
		}

		m_swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		m_swapchainCreateInfo.pNext = NULL;
		m_swapchainCreateInfo.flags = 0;
		m_swapchainCreateInfo.surface = *m_surface;
		m_swapchainCreateInfo.minImageCount = numberImages;

		m_swapchainCreateInfo.imageArrayLayers = 1;
		m_swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		m_swapchainCreateInfo.imageFormat = m_surface->getColorFormat();
		m_swapchainCreateInfo.imageColorSpace = m_surface->getColorSpace();
		m_swapchainCreateInfo.imageExtent = m_surface->getSurfaceCaps().currentExtent;
		m_swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		m_swapchainCreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
		m_swapchainCreateInfo.queueFamilyIndexCount = 0;
		m_swapchainCreateInfo.pQueueFamilyIndices = NULL;

		// Don't use VSYNC, just render as soon as possible.
		m_swapchainCreateInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
		m_swapchainCreateInfo.oldSwapchain = m_oldSwapchain;
		m_swapchainCreateInfo.clipped = true;
		m_swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		// If we recreate a SwapChain we have to destroy the previous one.
		// Note: destroying the swapchain also cleans up all its associated
		// presentable images once the platform is done with them.
		if(VK_NULL_HANDLE != m_oldSwapchain) {
			vkDestroySwapchainKHR(m_surface->getDevice(), m_oldSwapchain, NULL);
		}

		VkResult result = vkCreateSwapchainKHR(m_surface->getDevice(), &m_swapchainCreateInfo, NULL, &m_swapChain);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateSwapchainKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		//
		// Now let's get the number of available images from the swapchain.
		//
		uint32_t imageCount;
		result = vkGetSwapchainImagesKHR(m_surface->getDevice(), m_swapChain, &imageCount, NULL);
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetSwapchainImagesKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		std::vector<VkImage> images(imageCount);
		result = vkGetSwapchainImagesKHR(m_surface->getDevice(), m_swapChain, &imageCount, images.data());
		if(VK_SUCCESS != result) {
			std::cerr << "vkGetSwapchainImagesKHR failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		//
		// Now let's create the VkImageView for the VkImage's.
		//
		m_swapChainBuffers.reserve(imageCount);
		m_swapChainBuffers.resize(imageCount);

		for(size_t i = 0; i < images.size(); i++) {

			m_swapChainBuffers[i].image = images[i];

			VkImageViewCreateInfo imageViewCreateInfo {};
			imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewCreateInfo.format = m_swapchainCreateInfo.imageFormat;
			imageViewCreateInfo.components = {
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
				VK_COMPONENT_SWIZZLE_B,
				VK_COMPONENT_SWIZZLE_A
			};
			imageViewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			imageViewCreateInfo.image = m_swapChainBuffers[i].image;

			result = vkCreateImageView(m_surface->getDevice(), &imageViewCreateInfo, NULL, &m_swapChainBuffers[i].imageView);
			if(VK_SUCCESS != result) {
				std::cerr << "vkCreateImageView failed: " << vkf::vkVkResultToString(result) << std::endl;
				return result;
			}
		}

		VkFenceCreateInfo fenceCreateInfo {
			VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			NULL,
			0
		};

		result = vkCreateFence(m_surface->getDevice(), &fenceCreateInfo, NULL, &m_fence);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateFence failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		m_renderPass = new vkf::RenderPass(&m_surface->getDevice());
		m_renderPass->addColorAttachment(m_surface->getColorFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
		m_renderPass->addDepthStencilAttachment(m_depthStencilFormat, VK_IMAGE_LAYOUT_UNDEFINED);
		m_renderPass->init();

		result = setupDepthStencil();
		if(VK_SUCCESS != result) {
			return result;
		}

		return createFramebuffers(*m_renderPass);

	}

	VkResult SwapChain::createFramebuffers(RenderPass& renderPass) {
		// -------------------------------------------------------------------------
		// Create Framebuffer for each swapchain image.
		//
		VkResult result = VK_SUCCESS;
		m_frameBuffers.reserve(m_swapChainBuffers.size());
		m_frameBuffers.resize(m_swapChainBuffers.size());


		for(size_t idx = 0; idx < m_swapChainBuffers.size(); idx++) {
			std::vector<VkImageView> attachments;

			attachments.push_back(m_swapChainBuffers[idx].imageView);
			if(m_depthStencilImage.imageView != VK_NULL_HANDLE) {
				attachments.push_back(m_depthStencilImage.imageView);
			}

			VkFramebufferCreateInfo framebufferCreateInfo {};
			framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferCreateInfo.renderPass = renderPass;
			framebufferCreateInfo.attachmentCount = (uint32_t)attachments.size();
			framebufferCreateInfo.pAttachments = attachments.data();
			framebufferCreateInfo.width = m_surface->getExtent2D().width;
			framebufferCreateInfo.height = m_surface->getExtent2D().height;
			framebufferCreateInfo.layers = 1;

			result = vkCreateFramebuffer(m_surface->getDevice(), &framebufferCreateInfo, NULL, &m_frameBuffers[idx]);
		}
		return result;
		// -------------------------------------------------------------------------
	}

	VkResult SwapChain::setupDepthStencil() {

		VkImageCreateInfo image {};
		image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image.imageType = VK_IMAGE_TYPE_2D;
		image.format = m_depthStencilFormat;
		image.extent = { m_surface->getExtent2D().width, m_surface->getExtent2D().height, 1 };
		image.mipLevels = 1;
		image.arrayLayers = 1;
		image.samples = VK_SAMPLE_COUNT_1_BIT;
		image.tiling = VK_IMAGE_TILING_OPTIMAL;
		image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		image.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkResult result = vkCreateImage(m_surface->getDevice(), &image, NULL, &m_depthStencilImage.image);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateImage failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// Allocate memory for the image (device local) and bind it to our image
		VkMemoryAllocateInfo memAlloc {};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		VkMemoryRequirements memReqs;
		vkGetImageMemoryRequirements(m_surface->getDevice(), m_depthStencilImage.image, &memReqs);
		memAlloc.allocationSize = memReqs.size;
		memAlloc.memoryTypeIndex = getMemoryTypeIndex(m_surface->getDevice().getPhysicalDeviceMemoryProperties(), memReqs, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		result = vkAllocateMemory(m_surface->getDevice(), &memAlloc, NULL, &m_depthStencilImage.memory);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		result = vkBindImageMemory(m_surface->getDevice(), m_depthStencilImage.image, m_depthStencilImage.memory, 0);
		if(VK_SUCCESS != result) {
			std::cerr << "vkBindImageMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		VkImageViewCreateInfo depthStencilView {};
		depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
		depthStencilView.format = m_depthStencilFormat;
		depthStencilView.subresourceRange = {};
		depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		depthStencilView.subresourceRange.baseMipLevel = 0;
		depthStencilView.subresourceRange.levelCount = 1;
		depthStencilView.subresourceRange.baseArrayLayer = 0;
		depthStencilView.subresourceRange.layerCount = 1;
		depthStencilView.image = m_depthStencilImage.image;

		result = vkCreateImageView(m_surface->getDevice(), &depthStencilView, NULL, &m_depthStencilImage.imageView);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateImageView failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}


	void SwapChain::destroy() {

		if(NULL != m_renderPass) {
			m_renderPass->destroy();
			delete m_renderPass;
		}

		if(m_fence != VK_NULL_HANDLE) {
			vkDestroyFence(m_surface->getDevice(), m_fence, NULL);
			m_fence = VK_NULL_HANDLE;
		}

		//
		// Destroy all Framebuffers we created.
		//
		for(auto& framebuffer : m_frameBuffers) {
			vkDestroyFramebuffer(m_surface->getDevice(), framebuffer, NULL);
		}

		//
		// Destroy the ImageView of the Swapchain images.
		//
		if(m_swapChainBuffers.size() > 0) {
			for(auto bufferElement : m_swapChainBuffers) {
				// TODO According the specification we don't have to destroy manually. The image
				// will be destroyed by vkDestroySwapchainKHR already.
				//				vkDestroyImage(m_surface->getDevice(), bufferElement.image, NULL);
				vkDestroyImageView(m_surface->getDevice(), bufferElement.imageView, NULL);
			}
		}

		//
		// Free depth stencil if we have one.
		//
		if(m_depthStencilImage.imageView != VK_NULL_HANDLE) {
			vkFreeMemory(m_surface->getDevice(), m_depthStencilImage.memory, NULL);
			vkDestroyImage(m_surface->getDevice(), m_depthStencilImage.image, NULL);
			vkDestroyImageView(m_surface->getDevice(), m_depthStencilImage.imageView, NULL);
		}

		//
		// Destroy the swapchain itself.
		//
		if(VK_NULL_HANDLE != m_swapChain) {
			vkDestroySwapchainKHR(m_surface->getDevice(), m_swapChain, NULL);
			m_swapChain = VK_NULL_HANDLE;
		}
	}

	Surface* SwapChain::getSurface() const {
		return m_surface;
	}

	VkResult SwapChain::nextImage(uint32_t& imageIndices, Semaphore* presentSemaphore) {
		vkResetFences(m_surface->getDevice(), 1, &m_fence);

		VkResult result = vkAcquireNextImageKHR(m_surface->getDevice(), m_swapChain, UINT64_MAX, *presentSemaphore, m_fence, &imageIndices);
		if(result == VK_ERROR_OUT_OF_DATE_KHR) {
			std::cout << "VK_ERROR_OUT_OF_DATE_KHR" << std::endl;
		} else if(result == VK_SUBOPTIMAL_KHR) {
			std::cout << "VK_SUBOPTIMAL_KHR" << std::endl;
		} else {
			assert(!result);
		}
		vkWaitForFences(m_surface->getDevice(), 1, &m_fence, VK_TRUE, UINT64_MAX);
		return result;
	}

	VkResult SwapChain::present(Queue* queue, uint32_t imageIndices, Semaphore* renderingFinishedSemaphore) {

		VkPresentInfoKHR present;
		present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present.pNext = NULL;
		present.swapchainCount = 1;
		present.pSwapchains = &m_swapChain;
		present.pImageIndices = &imageIndices;
		present.waitSemaphoreCount = 1;
		present.pWaitSemaphores = *renderingFinishedSemaphore;
		present.pResults = NULL;

		VkResult result = vkQueuePresentKHR(*queue, &present);
		return result;
	}

	uint32_t SwapChain::getImageCount() {
		return m_swapChainBuffers.size();
	}

	VkImage SwapChain::getImage(uint32_t idx) const {
		return m_swapChainBuffers[idx].image;
	}

	VkFramebuffer SwapChain::getFramebuffer(uint32_t idx) const {
		return m_frameBuffers[idx];
	}

	std::vector<SwapChain::SwapChainImages>& SwapChain::getSwapImages() {
		return m_swapChainBuffers;
	}

	VkSwapchainCreateInfoKHR SwapChain::getSwapchainCreateInfo() const {
		return m_swapchainCreateInfo;
	}

//
//
//

	FrameBuffer::FrameBuffer(Device* device, RenderPass* renderPass)
		: m_device(device)
		, m_renderPass(renderPass)
		, m_width(0)
		, m_height(0)
		, m_swapChainDefinition(false) {
	}

	VkResult FrameBuffer::init() {
		return VK_SUCCESS;
	}

	VkResult FrameBuffer::create() {

		//
		// If user add color targets using SwapChain handle different.
		//
		if(m_swapChainDefinition) {

			//
			// OK, user added color target using swapchain. We will create for each swapchain image
			// one framebuffer with depth stencil if wanted.
			//
			for(auto& swapChainImageViews : m_colorAttachments) {
				std::vector<VkImageView> attachments;
				attachments.push_back(swapChainImageViews);

				if(m_depthStencilAttachment != NULL) {
					attachments.push_back(m_depthStencilAttachment->getImageView());
				}

				VkFramebufferCreateInfo frameBufferCreateInfo {};
				frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				frameBufferCreateInfo.renderPass = *m_renderPass;
				frameBufferCreateInfo.attachmentCount = attachments.size();
				frameBufferCreateInfo.pAttachments = attachments.data();
				frameBufferCreateInfo.width = m_width;
				frameBufferCreateInfo.height = m_height;
				frameBufferCreateInfo.layers = 1;

				// Create frame buffers for every swap chain image
				VkResult result = vkCreateFramebuffer(*m_device, &frameBufferCreateInfo, NULL, &m_frameBuffer);
				if(VK_SUCCESS != result) {
					std::cerr << "vkCreateFramebuffer failed: " << vkf::vkVkResultToString(result) << std::endl;
					return result;
				}
				m_swapChainDefinition = false;
			}
		} else {
			std::vector<VkImageView> attachments(m_colorAttachments);
			if(m_depthStencilAttachment != NULL) {
				attachments.push_back(m_depthStencilAttachment->getImageView());
			}

			VkFramebufferCreateInfo frameBufferCreateInfo {};
			frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			frameBufferCreateInfo.renderPass = *m_renderPass;
			frameBufferCreateInfo.attachmentCount = attachments.size();
			frameBufferCreateInfo.pAttachments = attachments.data();
			frameBufferCreateInfo.width = m_width;
			frameBufferCreateInfo.height = m_height;
			frameBufferCreateInfo.layers = 1;

			// Create frame buffers for every swap chain image
			VkResult result = vkCreateFramebuffer(*m_device, &frameBufferCreateInfo, NULL, &m_frameBuffer);
			if(VK_SUCCESS != result) {
				std::cerr << "vkCreateFramebuffer failed: " << vkf::vkVkResultToString(result) << std::endl;
				return result;
			}
		}
		return VK_SUCCESS;
	}

	VkResult FrameBuffer::addColor(SwapChain* swapChain) {

		for(auto& swapChainImage : swapChain->getSwapImages()) {
			m_colorAttachments.push_back(swapChainImage.imageView);
		}

		m_width = swapChain->getSwapchainCreateInfo().imageExtent.width;
		m_height = swapChain->getSwapchainCreateInfo().imageExtent.height;

		m_swapChainDefinition = true;

		return VK_SUCCESS;
	}

	VkResult FrameBuffer::addDepthStencil(VkFormat format, uint32_t width, uint32_t height) {

		if(NULL != m_depthStencilAttachment) {
			m_depthStencilAttachment->destroy();
			m_depthStencilAttachment = NULL;
		}

		m_depthStencilAttachment = new Texture2D(m_device, VK_FORMAT_D32_SFLOAT_S8_UINT, width, height);

		return m_depthStencilAttachment->init();
	}

//
//
//

	BufferBase::BufferBase(Device* device, VkBufferUsageFlagBits bufferUsageFlagBits, const BufferSize& size)
		: m_device(device)
		, m_bufferUsageFlagBits(bufferUsageFlagBits)
		, m_buffer(VK_NULL_HANDLE)
		, m_memory(VK_NULL_HANDLE)
		, m_memoryAllocateInfo {}
		, m_size(size)
		, m_initialized(false) {
	}

	BufferBase::~BufferBase() {
	}

	VkResult BufferBase::init() {
		VkBufferCreateInfo bufferCreateInfo {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.usage = m_bufferUsageFlagBits;
		bufferCreateInfo.size = m_size;

		VkResult result = vkCreateBuffer(*m_device, &bufferCreateInfo, NULL, &m_buffer);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateBuffer failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		vkGetBufferMemoryRequirements(*m_device, m_buffer, &m_memoryRequirements);

		m_memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		m_memoryAllocateInfo.pNext = NULL;
		m_memoryAllocateInfo.memoryTypeIndex = getMemoryTypeIndex(m_device->getPhysicalDeviceMemoryProperties(), m_memoryRequirements, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
		m_memoryAllocateInfo.allocationSize = m_memoryRequirements.size;
		result = vkAllocateMemory(*m_device, &m_memoryAllocateInfo, NULL, &m_memory);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			destroy();
			return result;
		}

		result = vkBindBufferMemory(*m_device, m_buffer, m_memory, 0);
		if(VK_SUCCESS != result) {
			std::cerr << "vkBindBufferMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			destroy();
			return result;
		}

		m_initialized = true;

		return result;
	}

	void* BufferBase::map() {
		assert(m_initialized != false && "You must initialize the buffer first.");

		void* data = NULL;
		VkResult result = vkMapMemory(*m_device, m_memory, 0, m_memoryAllocateInfo.allocationSize, 0, &data);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			return NULL;
		}
		return data;
	}

	void BufferBase::unmap() {
		vkUnmapMemory(*m_device, m_memory);
	}

	int BufferBase::upload(uint8_t* src, const BufferSize& size, uint64_t offset) {
		assert(m_initialized != false && "You must initialize the buffer first.");

		uint8_t* buffer;
		VkResult result = vkMapMemory(*m_device, m_memory, offset, m_memoryRequirements.size, 0, (void **)&buffer);
		if(VK_SUCCESS != result) {
			return -1;
		}

		memcpy(buffer, src, size);

		vkUnmapMemory(*m_device, m_memory);
		return 0;
	}

	void BufferBase::destroy() {
		if(VK_NULL_HANDLE != m_memory) {
			vkFreeMemory(*m_device, m_memory, NULL);
			m_memory = VK_NULL_HANDLE;
		}
		if(VK_NULL_HANDLE != m_buffer) {
			vkDestroyBuffer(*m_device, m_buffer, NULL);
			m_memory = VK_NULL_HANDLE;
		}
	}

	BufferBase& BufferBase::setSize(const BufferSize& size) {
		m_size = size;
		return *this;
	}

//
//
//

	VertexBuffer::VertexBuffer(Device* device, const BufferSize& size, BufferStride stride)
		: BufferBase(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size)
		, m_bidingID(0)
		, m_stride(stride) {
	}

	uint32_t VertexBuffer::getBindingID() const {
		return m_bidingID;
	}

	BufferStride VertexBuffer::getStride() const {
		return m_stride;
	}

	VertexBuffer& VertexBuffer::addElement(const BindingPoint& binding, const LocationPoint& location, VkFormat format, uint32_t offset) {
		VkVertexInputAttributeDescription vertexInputAttributeDescription {};
		vertexInputAttributeDescription.binding = binding;
		vertexInputAttributeDescription.location = location;
		vertexInputAttributeDescription.format = format;
		vertexInputAttributeDescription.offset = offset;

		m_vertexInputAttributeDescription.push_back(std::move(vertexInputAttributeDescription));
		return *this;
	}

	const std::vector<VkVertexInputAttributeDescription>& VertexBuffer::getVertexInputAttributeDescription() const {
		return m_vertexInputAttributeDescription;
	}

//
//
//

	IndexBuffer::IndexBuffer(Device* device, uint32_t numberOfIndicies, const BufferSize& size)
		: BufferBase(device, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size)
		, m_number(numberOfIndicies) {
	}

	uint32_t IndexBuffer::getNumberOfIndicies() const {
		return m_number;
	}

//
//
//

	UniformBuffer::UniformBuffer(Device* device, const BufferSize& size)
		: BufferBase(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size) {
	}

	VkDescriptorBufferInfo& UniformBuffer::getDescriptorBufferInfo() {
		descriptorBufferInfo = {m_buffer, 0, m_size};

		return descriptorBufferInfo;
	}

//
//
//

	StagingBuffer::StagingBuffer(Device* device, const BufferSize& size)
		: BufferBase(device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, size) {
	}

//
//
//

	DescriptorSetLayout::DescriptorSetLayout(Device* device)
		: m_device(device)
		, m_descriptorSetLayout(VK_NULL_HANDLE) {
	}

	DescriptorSetLayout& DescriptorSetLayout::add(const BindingPoint& binding, VkDescriptorType descriptorType, VkShaderStageFlags shaderStageFlags) {
		VkDescriptorSetLayoutBinding descriptorSetLayoutBinding {};
		descriptorSetLayoutBinding.binding = binding;
		descriptorSetLayoutBinding.descriptorType = descriptorType;
		descriptorSetLayoutBinding.stageFlags = shaderStageFlags;
		descriptorSetLayoutBinding.descriptorCount = 1; // TODO we need to adapt this in the case when we use arrays.

		m_bindings.push_back(descriptorSetLayoutBinding);
		return *this;
	}

	VkResult DescriptorSetLayout::init() {
		assert(m_bindings.size() > 0 && "You must bind at least one binding point.");

		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo {};
		descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(m_bindings.size());
		descriptorSetLayoutCreateInfo.pBindings = m_bindings.data();

		VkResult result = vkCreateDescriptorSetLayout(*m_device, &descriptorSetLayoutCreateInfo, NULL, &m_descriptorSetLayout);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDescriptorSetLayout failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void DescriptorSetLayout::destroy() {
		if(VK_NULL_HANDLE != m_descriptorSetLayout) {
			vkDestroyDescriptorSetLayout(*m_device, m_descriptorSetLayout, NULL);
			m_descriptorSetLayout = VK_NULL_HANDLE;
		}
	}

//
//
//

	DescriptorPool::DescriptorPool(Device* device)
		: m_device(device)
		, m_descriptorPool(VK_NULL_HANDLE) {
	}

	DescriptorPool& DescriptorPool::add(VkDescriptorType descriptorType, uint32_t count) {
		VkDescriptorPoolSize descriptorPoolSize;
		descriptorPoolSize.type = descriptorType;
		descriptorPoolSize.descriptorCount = count;

		m_types.push_back(descriptorPoolSize);
		return *this;
	}

	VkResult DescriptorPool::init() {
		assert(m_types.size() > 0 && "You must add at least one descriptor type.");

		VkDescriptorPoolCreateInfo descriptorPoolCreateInfo {};
		descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolCreateInfo.poolSizeCount = (uint32_t)m_types.size();
		descriptorPoolCreateInfo.pPoolSizes = m_types.data();
		descriptorPoolCreateInfo.maxSets = m_types.size();

		VkResult result = vkCreateDescriptorPool(*m_device, &descriptorPoolCreateInfo, NULL, &m_descriptorPool);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDescriptorPool failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void DescriptorPool::destroy() {
		if(VK_NULL_HANDLE != m_descriptorPool) {
			vkDestroyDescriptorPool(*m_device, m_descriptorPool, NULL);
			m_descriptorPool = VK_NULL_HANDLE;
		}
	}

//
//
//

	DescriptorSet::DescriptorSet(Device* device, DescriptorPool* descriptorPool, DescriptorSetLayout* layout)
		: m_device(device)
		, m_descriptorPool(descriptorPool)
		, m_layout(layout) {

	}

	void DescriptorSet::bind(const BindingPoint& binding, UniformBuffer* uniformBuffer) {
		m_descriptorBufferInfo[binding] = uniformBuffer->getDescriptorBufferInfo();

		VkWriteDescriptorSet write {};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorCount = 1; // TODO Do we need to adapt something here?
		write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		write.pBufferInfo = &m_descriptorBufferInfo[binding];
		write.dstBinding = binding;

		m_writeDescriptorSets.push_back(write);
	}

	void DescriptorSet::bind(const BindingPoint& binding, vkf::Texture* texture, vkf::TextureSampler* textureSampler) {
		VkDescriptorImageInfo descriptorImageInfo {};
		if(texture) {
			descriptorImageInfo.imageView = texture->getImageView();
			descriptorImageInfo.imageLayout = texture->getImageLayout();
		}
		if(textureSampler) {
			descriptorImageInfo.sampler = *textureSampler;
		}

		m_descriptorImageInfo[binding] = descriptorImageInfo;

		VkWriteDescriptorSet write {};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorCount = 1; // TODO Do we need to adapt something here?
		write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		write.pImageInfo = &m_descriptorImageInfo[binding];
		write.dstBinding = binding;

		m_writeDescriptorSets.push_back(write);
	}


	VkResult DescriptorSet::init() {
		assert((m_writeDescriptorSets.size() != 0) && "You have to add at least one uniform buffer in your descriptor set.");

		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo {};
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocateInfo.descriptorPool = *m_descriptorPool;
		descriptorSetAllocateInfo.descriptorSetCount = 1;
		descriptorSetAllocateInfo.pSetLayouts = *m_layout;

		VkResult result = vkAllocateDescriptorSets(*m_device, &descriptorSetAllocateInfo, &m_descriptorSet);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateDescriptorSets failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		for(auto& writeDescriptorSet : m_writeDescriptorSets) {
			writeDescriptorSet.dstSet = m_descriptorSet;
		}

		vkUpdateDescriptorSets(*m_device, m_writeDescriptorSets.size(), m_writeDescriptorSets.data(), 0, NULL);
		return result;
	}

	void DescriptorSet::destroy() {
		if(VK_NULL_HANDLE != m_descriptorSet) {
			vkFreeDescriptorSets(*m_device, *m_descriptorPool, 1, &m_descriptorSet);
			m_descriptorSet = VK_NULL_HANDLE;
		}
	}

//
//
//

	PipelineCache::PipelineCache(Device* device)
		: m_device(device)
		, m_pipeLineCache(VK_NULL_HANDLE) {
	}

	PipelineCache::~PipelineCache() {

	}

	VkResult PipelineCache::init() {
		VkPipelineCacheCreateInfo pipelineCacheCreateInfo {};
		pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		VkResult result = vkCreatePipelineCache(*m_device, &pipelineCacheCreateInfo, NULL, &m_pipeLineCache);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateRenderPass failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void PipelineCache::destroy() {
		if(VK_NULL_HANDLE != m_pipeLineCache) {
			vkDestroyPipelineCache(*m_device, m_pipeLineCache, NULL);
			m_pipeLineCache = VK_NULL_HANDLE;
		}
	}

//
//
//

	ShaderModule::ShaderModule(Device* device, VkShaderStageFlagBits shaderStageFalgBits, const std::string& entryName)
		: m_device(device)
		, m_shaderModule(VK_NULL_HANDLE)
		, m_shaderStageFlagBits(shaderStageFalgBits)
		, m_name(entryName) {

	}

	ShaderModule::~ShaderModule() {

	}

	bool ShaderModule::load(const FileName& filename) {

		std::ifstream is(filename, std::ios::binary | std::ios::in | std::ios::ate);
		if(is.is_open()) {

			//
			// Get the size of the binary file.
			//
			std::ifstream::pos_type shaderSize = is.tellg();
			is.seekg(0, std::ios::beg);
			std::string shaderCode;
			shaderCode.reserve(shaderSize);
			shaderCode.resize(shaderSize);

			is.read((char*)shaderCode.data(), shaderSize);
			is.close();

			if(0 == shaderSize) {
				std::cerr << "When trying to load the SPRIV shader it seems like the size is = 0." << std::endl;
				return false;
			}

			//
			// Create the Vulkan Shader Module.
			//
			VkShaderModuleCreateInfo moduleCreateInfo {};
			moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			moduleCreateInfo.codeSize = shaderSize;
			moduleCreateInfo.pCode = (uint32_t*)shaderCode.data();

			VkResult result = vkCreateShaderModule(*m_device, &moduleCreateInfo, NULL, &m_shaderModule);
			if(VK_SUCCESS != result) {
				std::cerr << "vkCreateShaderModule failed: " << vkf::vkVkResultToString(result) << std::endl;
				return false;
			}

			return true;
		}
		return false;
	}

	void ShaderModule::destroy() {
		if(VK_NULL_HANDLE != m_shaderModule) {
			vkDestroyShaderModule(*m_device, m_shaderModule, NULL);
			m_shaderModule = VK_NULL_HANDLE;
		}
	}

	VkShaderStageFlagBits ShaderModule::getShaderStageFlagBits() const {
		return m_shaderStageFlagBits;
	}

	const char* ShaderModule::getName() const {
		return m_name.c_str();
	}

//
//
//

	VertexShader::VertexShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_VERTEX_BIT) {
	}

//
//
//

	GeometryShader::GeometryShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_GEOMETRY_BIT) {
	}

//
//
//

	FragmentShader::FragmentShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_FRAGMENT_BIT) {
	}

//
//
//

	TesselationControlShader::TesselationControlShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT) {
	}

//
//
//

	TesselationEvaluationShader::TesselationEvaluationShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT) {
	}

//
//
//

	ComputeShader::ComputeShader(Device* device)
		: ShaderModule(device, VK_SHADER_STAGE_COMPUTE_BIT) {
	}

//
//
//
	Texture::Texture(Device* device)
		: m_device(device)
		, m_image(VK_NULL_HANDLE)
		, m_imageView(VK_NULL_HANDLE)
		, m_sampler(VK_NULL_HANDLE)
		, m_imageType(VK_IMAGE_TYPE_2D)
		, m_imageViewType(VK_IMAGE_VIEW_TYPE_2D)
		, m_memoryAllocateInfo {}
		, m_memory(VK_NULL_HANDLE)
		, m_width(0)
		, m_height(0)
		, m_depth(1)   {
	}

	Texture::Texture(Device* device,
	                 VkImageLayout imageTextureLayout,
	                 VkImageType imageType,
	                 VkImageViewType imageViewType,
	                 VkFormat format,
	                 uint32_t width,
	                 uint32_t height,
	                 uint32_t depth)
		: m_device(device)
		, m_image(VK_NULL_HANDLE)
		, m_imageView(VK_NULL_HANDLE)
		, m_sampler(VK_NULL_HANDLE)
		, m_imageType(imageType)
		, m_imageViewType(VK_IMAGE_VIEW_TYPE_2D)
		, m_format(format)
		, m_imageLayout(imageTextureLayout)
		, m_memoryAllocateInfo {}
		, m_memory(VK_NULL_HANDLE)
		, m_width(width)
		, m_height(height)
		, m_depth(depth) {
	}

	Texture::~Texture() {
	}

	VkResult Texture::init() {
		VkImageCreateInfo imageCreateInfo;
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.pNext = NULL;
		imageCreateInfo.flags = 0;
		imageCreateInfo.imageType = m_imageType;
		imageCreateInfo.format = m_format;
		imageCreateInfo.extent.width = m_width;
		imageCreateInfo.extent.height = m_height;
		imageCreateInfo.extent.depth = (m_imageType==VK_IMAGE_TYPE_3D) ? 1 : m_depth;
		imageCreateInfo.mipLevels = 1;
		imageCreateInfo.arrayLayers = m_depth;
		imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageCreateInfo.queueFamilyIndexCount = 0;
		imageCreateInfo.pQueueFamilyIndices = 0;
		imageCreateInfo.initialLayout = m_imageLayout;

		VkResult result = vkCreateImage(*m_device, &imageCreateInfo, NULL, &m_image);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateImage failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		vkGetImageMemoryRequirements(*m_device, m_image, &m_memoryRequirements);

		m_memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		m_memoryAllocateInfo.pNext = NULL;
		m_memoryAllocateInfo.memoryTypeIndex = getMemoryTypeIndex(m_device->getPhysicalDeviceMemoryProperties(), m_memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_memoryAllocateInfo.allocationSize = m_memoryRequirements.size;
		result = vkAllocateMemory(*m_device, &m_memoryAllocateInfo, NULL, &m_memory);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		result = vkBindImageMemory(*m_device, m_image, m_memory, 0);
		if(VK_SUCCESS != result) {
			std::cerr << "vkBindBufferMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		VkImageViewCreateInfo imageViewCreateInfo {};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.viewType = m_imageViewType;
		imageViewCreateInfo.format = m_format;
		imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		imageViewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		imageViewCreateInfo.subresourceRange.layerCount = (m_imageViewType == VK_IMAGE_VIEW_TYPE_CUBE) ? 1 : 6;
		imageViewCreateInfo.subresourceRange.levelCount = 1; // MipMapLevels
		imageViewCreateInfo.image = m_image;

		result = vkCreateImageView(*m_device, &imageViewCreateInfo, NULL, &m_imageView);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateImageView failed: " << vkf::vkVkResultToString(result) << std::endl;
		}

		VkImageSubresource imageSubresource {};
		imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		VkSubresourceLayout subresourceLayout {};
		vkGetImageSubresourceLayout(*m_device, m_image, &imageSubresource, &subresourceLayout);

		return result;
	}

	VkResult Texture::init(VkImageLayout imageTextureLayout, VkImageType imageType, VkImageViewType imageViewType, VkFormat format, uint32_t width, uint32_t height, uint32_t depth) {
		m_imageLayout = imageTextureLayout;
		m_imageType = imageType;
		m_imageViewType = imageViewType;
		m_format = format;
		m_width = width;
		m_height = height;
		m_depth = depth;
		return init();
	}

	void Texture::destroy() {
		if(VK_NULL_HANDLE != m_memory) {
			vkFreeMemory(*m_device, m_memory, NULL);
			m_memory = VK_NULL_HANDLE;
		}
		if(VK_NULL_HANDLE != m_image) {
			vkDestroyImage(*m_device, m_image, NULL);
			m_image = VK_NULL_HANDLE;
		}
	}

	void* Texture::map() {
		void* data = NULL;
		VkResult result = vkMapMemory(*m_device, m_memory, 0, m_memoryAllocateInfo.allocationSize, 0, &data);
		if(VK_SUCCESS != result) {
			std::cerr << "vkAllocateMemory failed: " << vkf::vkVkResultToString(result) << std::endl;
			return NULL;
		}
		return data;
	}

	void Texture::unmap() {
		vkUnmapMemory(*m_device, m_memory);
	}

	VkResult Texture::upload(uint8_t* src, const BufferSize& size, uint64_t offset) {
		uint8_t* buffer;
		VkResult result = vkMapMemory(*m_device, m_memory, offset, m_memoryRequirements.size, 0, (void **)&buffer);
		if(VK_SUCCESS != result) {
			return result;
		}

		memcpy(buffer, src, size);

		vkUnmapMemory(*m_device, m_memory);
		return result;
	}

	uint32_t Texture::getWidth() const {
		return m_width;
	}

	uint32_t Texture::getHeight() const {
		return m_height;
	}

	uint32_t Texture::getDepth() const {
		return m_depth;
	}

	size_t Texture::getSize() {
		return m_memoryAllocateInfo.allocationSize;
	}

	VkFormat Texture::getFormat() const {
		return m_format;
	}

	VkImage Texture::getImage() const {
		return m_image;
	}

	VkImageView Texture::getImageView() const {
		return m_imageView;
	}

	VkImageLayout Texture::getImageLayout() const {
		return m_imageLayout;
	}


//
//
//

	TextureSampler::TextureSampler(Device* device)
		: m_device(device) {
		m_samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		m_samplerCreateInfo.pNext = NULL;
		m_samplerCreateInfo.magFilter = VK_FILTER_NEAREST;
		m_samplerCreateInfo.minFilter = VK_FILTER_NEAREST;
		m_samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_samplerCreateInfo.anisotropyEnable = VK_FALSE;
		m_samplerCreateInfo.maxAnisotropy = 0;
		m_samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		m_samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
		m_samplerCreateInfo.compareEnable = VK_FALSE;
		m_samplerCreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		m_samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
		m_samplerCreateInfo.mipLodBias = 0.0f;
		m_samplerCreateInfo.minLod = 0.0f;
		m_samplerCreateInfo.maxLod = 0.0f;

	}

	VkResult TextureSampler::init() {
		VkResult result = vkCreateSampler(*m_device, &m_samplerCreateInfo, NULL, &m_textureSampler);
		return result;
	}

	void TextureSampler::destroy() {
		vkDestroySampler(*m_device, m_textureSampler, NULL);
	}

	TextureSampler& TextureSampler::setMinFilter(VkFilter minFilter) {
		m_samplerCreateInfo.minFilter = minFilter;
		return *this;
	}

	TextureSampler& TextureSampler::setMagFilter(VkFilter magFilter) {
		m_samplerCreateInfo.magFilter = magFilter;
		return *this;
	}

	TextureSampler& TextureSampler::setAddressModeU(VkSamplerAddressMode U) {
		m_samplerCreateInfo.addressModeU = U;
		return *this;
	}

	TextureSampler& TextureSampler::setAddressModeV(VkSamplerAddressMode V) {
		m_samplerCreateInfo.addressModeV = V;
		return *this;
	}

	TextureSampler& TextureSampler::setAddressModeW(VkSamplerAddressMode W) {
		m_samplerCreateInfo.addressModeW = W;
		return *this;
	}

//
//
//

	Pipeline::Pipeline(Device* device, DescriptorSetLayout* descriptorSetLayout, RenderPass* renderPass, VkExtent2D extent2D)
		: m_device(device)
		, m_descriptorSetLayout(descriptorSetLayout)
		, m_renderPass(renderPass)
		, m_pipelineLayout(VK_NULL_HANDLE)
		, m_pipeline(VK_NULL_HANDLE)
		, m_pipelineVertexInputStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, NULL, 0, 0,
		    NULL, 0, NULL
		                                       }
		, m_extent2D(extent2D) {

		// -------------------------------------------------------------------------
		// Rasterization state
		//
		memset(&m_rasterizationStateCreateInfo, 0, sizeof(VkPipelineRasterizationStateCreateInfo));
		m_rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		m_rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		m_rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
		m_rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
		m_rasterizationStateCreateInfo.lineWidth = 1.0f;
		m_rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
		m_rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		m_rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

		// -------------------------------------------------------------------------


		// -------------------------------------------------------------------------
		// Input assembly state.
		//
		memset(&m_inputAssemblyState, 0, sizeof(VkPipelineInputAssemblyStateCreateInfo));
		m_inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		m_inputAssemblyState.pNext = NULL;
		m_inputAssemblyState.flags = 0;
		m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		m_inputAssemblyState.primitiveRestartEnable = VK_FALSE;

		// -------------------------------------------------------------------------

		// -------------------------------------------------------------------------
		// Set Viewport states.
		//
		VkViewport viewport {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = m_extent2D.width;
		viewport.height = m_extent2D.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		m_viewports.push_back(viewport);

		VkRect2D scissor;
		scissor.extent.width = m_extent2D.width;
		scissor.extent.height = m_extent2D.height;
		scissor.offset.x = 0;
		scissor.offset.y = 0;

		m_scissors.push_back(scissor);

		// -------------------------------------------------------------------------

		// -------------------------------------------------------------------------
		// Depth and stencil state
		//

		m_depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		m_depthStencilState.depthTestEnable = VK_TRUE;
		m_depthStencilState.depthWriteEnable = VK_TRUE;
		m_depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		m_depthStencilState.depthBoundsTestEnable = VK_FALSE;
		m_depthStencilState.back.failOp = VK_STENCIL_OP_KEEP;
		m_depthStencilState.back.passOp = VK_STENCIL_OP_KEEP;
		m_depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;
		m_depthStencilState.stencilTestEnable = VK_FALSE;
		m_depthStencilState.front = m_depthStencilState.back;

		// -------------------------------------------------------------------------

	}

	Pipeline::~Pipeline() {

	}

	VkResult Pipeline::init() {

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = 1;
		pipelineLayoutCreateInfo.pSetLayouts = *m_descriptorSetLayout;

		VkResult result = vkCreatePipelineLayout(*m_device, &pipelineLayoutCreateInfo, NULL, &m_pipelineLayout);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDescriptorSetLayout failed: " << vkf::vkVkResultToString(result) << std::endl;
			return result;
		}

		// Blending is not used in this example
		VkPipelineColorBlendAttachmentState blendAttachmentState {};
		blendAttachmentState.colorWriteMask = 0xf;
		blendAttachmentState.blendEnable = VK_FALSE;

		// Color blend state
		// Describes blend modes and color masks
		VkPipelineColorBlendStateCreateInfo colorBlendState = {};
		colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendState.attachmentCount = 1;
		colorBlendState.pAttachments = &blendAttachmentState;


		VkPipelineViewportStateCreateInfo viewportState {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = static_cast<uint32_t>(m_viewports.size());
		viewportState.pViewports = m_viewports.data();
		viewportState.scissorCount = static_cast<uint32_t>(m_scissors.size());
		viewportState.pScissors = m_scissors.data();

		VkPipelineDynamicStateCreateInfo dynamicState {};
		std::vector<VkDynamicState> dynamicStateEnables;
		dynamicStateEnables.push_back(VK_DYNAMIC_STATE_VIEWPORT);
		dynamicStateEnables.push_back(VK_DYNAMIC_STATE_SCISSOR);
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.pDynamicStates = dynamicStateEnables.data();
		dynamicState.dynamicStateCount = dynamicStateEnables.size();

		// Multi sampling state
		VkPipelineMultisampleStateCreateInfo multisampleState {};
		multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleState.sampleShadingEnable = VK_FALSE;
		multisampleState.minSampleShading = 0.0f;
		multisampleState.pSampleMask = NULL;
		multisampleState.alphaToCoverageEnable = VK_FALSE;
		multisampleState.alphaToOneEnable = VK_FALSE;

		VkGraphicsPipelineCreateInfo pipelineCreateInfo {};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.pNext = NULL;

		// Don't optimize this pipeline, will be created faster but not optimized.
		pipelineCreateInfo.flags = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;

		// Set shader stages.
		pipelineCreateInfo.stageCount = m_shaderStages.size();
		pipelineCreateInfo.pStages = m_shaderStages.data();

		// Set vertex input state so the pipeline has access to the vertex data.
		if(m_pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount > 0) {
			pipelineCreateInfo.pVertexInputState = &m_pipelineVertexInputStateCreateInfo;
		}

		pipelineCreateInfo.pInputAssemblyState = &m_inputAssemblyState;
		pipelineCreateInfo.pTessellationState = NULL;
		pipelineCreateInfo.pViewportState = &viewportState;
		pipelineCreateInfo.pRasterizationState = &m_rasterizationStateCreateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleState;
		pipelineCreateInfo.pDepthStencilState = &m_depthStencilState;
		pipelineCreateInfo.pColorBlendState = &colorBlendState;
		pipelineCreateInfo.pDynamicState = &dynamicState;
		pipelineCreateInfo.layout = m_pipelineLayout;
		pipelineCreateInfo.renderPass = *m_renderPass;
		pipelineCreateInfo.subpass = 0;
		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = 0;

		result = vkCreateGraphicsPipelines(*m_device, NULL, 1, &pipelineCreateInfo, NULL, &m_pipeline);
		if(VK_SUCCESS != result) {
			std::cerr << "vkCreateDescriptorSetLayout failed: " << vkf::vkVkResultToString(result) << std::endl;
		}
		return result;
	}

	void Pipeline::destroy() {
		if(VK_NULL_HANDLE != m_pipelineLayout) {
			vkDestroyPipelineLayout(*m_device, m_pipelineLayout, NULL);
			m_pipelineLayout = VK_NULL_HANDLE;
		}
		if(VK_NULL_HANDLE != m_pipeline) {
			vkDestroyPipeline(*m_device, m_pipeline, NULL);
			m_pipeline = VK_NULL_HANDLE;
		}
	}

	void Pipeline::addVertexState(VertexBuffer* vertexBuffer) {


		m_vertexInputBindingDescription.binding = vertexBuffer->getBindingID();
		m_vertexInputBindingDescription.stride = vertexBuffer->getStride();
		m_vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		m_pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		m_pipelineVertexInputStateCreateInfo.pNext = NULL;
		m_pipelineVertexInputStateCreateInfo.flags = 0;
		m_pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
		m_pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &m_vertexInputBindingDescription;
		m_pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = vertexBuffer->getVertexInputAttributeDescription().size();
		m_pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexBuffer->getVertexInputAttributeDescription().data();
	}

	void Pipeline::addIndexState(IndexBuffer* indexBuffer) {

	}

	void Pipeline::addShaderModule(ShaderModule* shaderModule) {

		for(auto& info : m_shaderStages) {
			if(info.stage == shaderModule->getShaderStageFlagBits()) {
				std::cerr << "The shader stage is already set. " << std::endl;
				exit(1);
			}
		}

		VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo;
		pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipelineShaderStageCreateInfo.pNext = NULL;
		pipelineShaderStageCreateInfo.flags = 0;
		pipelineShaderStageCreateInfo.stage = shaderModule->getShaderStageFlagBits();
		pipelineShaderStageCreateInfo.module = *shaderModule;
		// A pointer to a null-terminated UTF-8 string specifying the entry point name of the shader for this stage
		pipelineShaderStageCreateInfo.pName = shaderModule->getName();
		pipelineShaderStageCreateInfo.pSpecializationInfo = NULL;

		m_shaderStages.push_back(pipelineShaderStageCreateInfo);
	}

	Pipeline& Pipeline::setUsedTopology(VkPrimitiveTopology primitiveTopology) {
		m_inputAssemblyState.topology = primitiveTopology;
		return *this;
	}

	VkPipelineLayout Pipeline::getPipelineLayout() const {
		return m_pipelineLayout;
	}

	Pipeline& Pipeline::setCullMode(VkCullModeFlags cullModeFlags) {
		m_rasterizationStateCreateInfo.cullMode = cullModeFlags;
		return *this;
	}

	Pipeline& Pipeline::setFrontFace(VkFrontFace frontFace) {
		m_rasterizationStateCreateInfo.frontFace = frontFace;
		return *this;
	}

	Pipeline& Pipeline::setEnableDepthStencil(VkBool32 enable) {
		m_depthStencilState.depthTestEnable = enable;
		return *this;
	}


}
