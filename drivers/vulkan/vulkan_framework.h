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

#ifndef VULKAN_FRAMEWORK_H
#define VULKAN_FRAMEWORK_H

#define VKF_CHECK(A) assert(A)

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <cassert>
#include <memory>
#include <string.h>
#include <limits>
#include <fstream>
#include <sstream>
#include <map>

#ifdef VKF_STATIC
#  define VKFAPI extern
#else
#  if defined(__GNUC__) && __GNUC__>=4
#   define VKFAPI extern __attribute__ ((visibility("default")))
#  elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#   define VKFAPI extern __global
#  else
#   define VKFAPI extern
#  endif
#endif

#define VKF_VAR_EXPORT VKFAPI
#define VKF_FUN_EXPORT VKFAPI

#define CHECK_VULKAN(VULKAN_FUNCTION) 	{ \
		VkResult result = VULKAN_FUNCTION; \
		if(VK_SUCCESS != result) { \
			std::cerr <<  #VULKAN_FUNCTION << " failed: " << vkf::vkVkResultToString(result) << std::endl; \
			exit(1); \
		} \
	} \

// Macro to get a procedure address based on a vulkan instance
#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)                                            \
	{                                                                                       \
		vk##entrypoint = (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint); \
		if(vk##entrypoint == NULL) {                                                        \
			std::cerr << "Couldn't get Vulkan Instance Procedur Address: "                  \
			          << "vk" #entrypoint << std::endl;                                     \
			exit(1);                                                                        \
		}                                                                                   \
	}

// Macro to get a procedure address based on a vulkan device
#define GET_DEVICE_PROC_ADDR(dev, entrypoint)                                            \
	{                                                                                    \
		vk##entrypoint = (PFN_vk##entrypoint)vkGetDeviceProcAddr(dev, "vk" #entrypoint); \
		if(vk##entrypoint == NULL) {                                                     \
			std::cerr << "Couldn't get Vulkan Device Procedur Address: "                 \
			          << "vk" #entrypoint << std::endl;                                  \
			exit(1);                                                                     \
		}                                                                                \
	}

#define VKF_FUNCTION_EXPORT(entrypoint) VKF_VAR_EXPORT PFN_##entrypoint entrypoint;
#define VKF_FUNCTION_DEFINE(entrypoint) PFN_##entrypoint entrypoint = NULL;
#define VKF_INSTANCE_FUNCTION_LOAD(LIBRARY, entrypoint) entrypoint = (PFN_##entrypoint)vkGetInstanceProcAddr(NULL, #entrypoint);
#define VKF_DEVICE_FUNCTION_LOAD(LIBRARY, entrypoint) entrypoint = (PFN_##entrypoint)vkGetDeviceProcAddr(NULL, #entrypoint);

// -----------------------------------------------------------------------------
// Vulkan 1.0
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkCreateInstance)
VKF_FUNCTION_EXPORT(vkDestroyInstance)
VKF_FUNCTION_EXPORT(vkEnumeratePhysicalDevices)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFeatures)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFormatProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceImageFormatProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceQueueFamilyProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceMemoryProperties)
VKF_FUNCTION_EXPORT(vkGetInstanceProcAddr)
VKF_FUNCTION_EXPORT(vkGetDeviceProcAddr)
VKF_FUNCTION_EXPORT(vkCreateDevice)
VKF_FUNCTION_EXPORT(vkDestroyDevice)
VKF_FUNCTION_EXPORT(vkEnumerateInstanceExtensionProperties)
VKF_FUNCTION_EXPORT(vkEnumerateDeviceExtensionProperties)
VKF_FUNCTION_EXPORT(vkEnumerateInstanceLayerProperties)
VKF_FUNCTION_EXPORT(vkEnumerateDeviceLayerProperties)
VKF_FUNCTION_EXPORT(vkGetDeviceQueue)
VKF_FUNCTION_EXPORT(vkQueueSubmit)
VKF_FUNCTION_EXPORT(vkQueueWaitIdle)
VKF_FUNCTION_EXPORT(vkDeviceWaitIdle)
VKF_FUNCTION_EXPORT(vkAllocateMemory)
VKF_FUNCTION_EXPORT(vkFreeMemory)
VKF_FUNCTION_EXPORT(vkMapMemory)
VKF_FUNCTION_EXPORT(vkUnmapMemory)
VKF_FUNCTION_EXPORT(vkFlushMappedMemoryRanges)
VKF_FUNCTION_EXPORT(vkInvalidateMappedMemoryRanges)
VKF_FUNCTION_EXPORT(vkGetDeviceMemoryCommitment)
VKF_FUNCTION_EXPORT(vkBindBufferMemory)
VKF_FUNCTION_EXPORT(vkBindImageMemory)
VKF_FUNCTION_EXPORT(vkGetBufferMemoryRequirements)
VKF_FUNCTION_EXPORT(vkGetImageMemoryRequirements)
VKF_FUNCTION_EXPORT(vkGetImageSparseMemoryRequirements)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSparseImageFormatProperties)
VKF_FUNCTION_EXPORT(vkQueueBindSparse)
VKF_FUNCTION_EXPORT(vkCreateFence)
VKF_FUNCTION_EXPORT(vkDestroyFence)
VKF_FUNCTION_EXPORT(vkResetFences)
VKF_FUNCTION_EXPORT(vkGetFenceStatus)
VKF_FUNCTION_EXPORT(vkWaitForFences)
VKF_FUNCTION_EXPORT(vkCreateSemaphore)
VKF_FUNCTION_EXPORT(vkDestroySemaphore)
VKF_FUNCTION_EXPORT(vkCreateEvent)
VKF_FUNCTION_EXPORT(vkDestroyEvent)
VKF_FUNCTION_EXPORT(vkGetEventStatus)
VKF_FUNCTION_EXPORT(vkSetEvent)
VKF_FUNCTION_EXPORT(vkResetEvent)
VKF_FUNCTION_EXPORT(vkCreateQueryPool)
VKF_FUNCTION_EXPORT(vkDestroyQueryPool)
VKF_FUNCTION_EXPORT(vkGetQueryPoolResults)
VKF_FUNCTION_EXPORT(vkCreateBuffer)
VKF_FUNCTION_EXPORT(vkDestroyBuffer)
VKF_FUNCTION_EXPORT(vkCreateBufferView)
VKF_FUNCTION_EXPORT(vkDestroyBufferView)
VKF_FUNCTION_EXPORT(vkCreateImage)
VKF_FUNCTION_EXPORT(vkDestroyImage)
VKF_FUNCTION_EXPORT(vkGetImageSubresourceLayout)
VKF_FUNCTION_EXPORT(vkCreateImageView)
VKF_FUNCTION_EXPORT(vkDestroyImageView)
VKF_FUNCTION_EXPORT(vkCreateShaderModule)
VKF_FUNCTION_EXPORT(vkDestroyShaderModule)
VKF_FUNCTION_EXPORT(vkCreatePipelineCache)
VKF_FUNCTION_EXPORT(vkDestroyPipelineCache)
VKF_FUNCTION_EXPORT(vkGetPipelineCacheData)
VKF_FUNCTION_EXPORT(vkMergePipelineCaches)
VKF_FUNCTION_EXPORT(vkCreateGraphicsPipelines)
VKF_FUNCTION_EXPORT(vkCreateComputePipelines)
VKF_FUNCTION_EXPORT(vkDestroyPipeline)
VKF_FUNCTION_EXPORT(vkCreatePipelineLayout)
VKF_FUNCTION_EXPORT(vkDestroyPipelineLayout)
VKF_FUNCTION_EXPORT(vkCreateSampler)
VKF_FUNCTION_EXPORT(vkDestroySampler)
VKF_FUNCTION_EXPORT(vkCreateDescriptorSetLayout)
VKF_FUNCTION_EXPORT(vkDestroyDescriptorSetLayout)
VKF_FUNCTION_EXPORT(vkCreateDescriptorPool)
VKF_FUNCTION_EXPORT(vkDestroyDescriptorPool)
VKF_FUNCTION_EXPORT(vkResetDescriptorPool)
VKF_FUNCTION_EXPORT(vkAllocateDescriptorSets)
VKF_FUNCTION_EXPORT(vkFreeDescriptorSets)
VKF_FUNCTION_EXPORT(vkUpdateDescriptorSets)
VKF_FUNCTION_EXPORT(vkCreateFramebuffer)
VKF_FUNCTION_EXPORT(vkDestroyFramebuffer)
VKF_FUNCTION_EXPORT(vkCreateRenderPass)
VKF_FUNCTION_EXPORT(vkDestroyRenderPass)
VKF_FUNCTION_EXPORT(vkGetRenderAreaGranularity)
VKF_FUNCTION_EXPORT(vkCreateCommandPool)
VKF_FUNCTION_EXPORT(vkDestroyCommandPool)
VKF_FUNCTION_EXPORT(vkResetCommandPool)
VKF_FUNCTION_EXPORT(vkAllocateCommandBuffers)
VKF_FUNCTION_EXPORT(vkFreeCommandBuffers)
VKF_FUNCTION_EXPORT(vkBeginCommandBuffer)
VKF_FUNCTION_EXPORT(vkEndCommandBuffer)
VKF_FUNCTION_EXPORT(vkResetCommandBuffer)
VKF_FUNCTION_EXPORT(vkCmdBindPipeline)
VKF_FUNCTION_EXPORT(vkCmdSetViewport)
VKF_FUNCTION_EXPORT(vkCmdSetScissor)
VKF_FUNCTION_EXPORT(vkCmdSetLineWidth)
VKF_FUNCTION_EXPORT(vkCmdSetDepthBias)
VKF_FUNCTION_EXPORT(vkCmdSetBlendConstants)
VKF_FUNCTION_EXPORT(vkCmdSetDepthBounds)
VKF_FUNCTION_EXPORT(vkCmdSetStencilCompareMask)
VKF_FUNCTION_EXPORT(vkCmdSetStencilWriteMask)
VKF_FUNCTION_EXPORT(vkCmdSetStencilReference)
VKF_FUNCTION_EXPORT(vkCmdBindDescriptorSets)
VKF_FUNCTION_EXPORT(vkCmdBindIndexBuffer)
VKF_FUNCTION_EXPORT(vkCmdBindVertexBuffers)
VKF_FUNCTION_EXPORT(vkCmdDraw)
VKF_FUNCTION_EXPORT(vkCmdDrawIndexed)
VKF_FUNCTION_EXPORT(vkCmdDrawIndirect)
VKF_FUNCTION_EXPORT(vkCmdDrawIndexedIndirect)
VKF_FUNCTION_EXPORT(vkCmdDispatch)
VKF_FUNCTION_EXPORT(vkCmdDispatchIndirect)
VKF_FUNCTION_EXPORT(vkCmdCopyBuffer)
VKF_FUNCTION_EXPORT(vkCmdCopyImage)
VKF_FUNCTION_EXPORT(vkCmdBlitImage)
VKF_FUNCTION_EXPORT(vkCmdCopyBufferToImage)
VKF_FUNCTION_EXPORT(vkCmdCopyImageToBuffer)
VKF_FUNCTION_EXPORT(vkCmdUpdateBuffer)
VKF_FUNCTION_EXPORT(vkCmdFillBuffer)
VKF_FUNCTION_EXPORT(vkCmdClearColorImage)
VKF_FUNCTION_EXPORT(vkCmdClearDepthStencilImage)
VKF_FUNCTION_EXPORT(vkCmdClearAttachments)
VKF_FUNCTION_EXPORT(vkCmdResolveImage)
VKF_FUNCTION_EXPORT(vkCmdSetEvent)
VKF_FUNCTION_EXPORT(vkCmdResetEvent)
VKF_FUNCTION_EXPORT(vkCmdWaitEvents)
VKF_FUNCTION_EXPORT(vkCmdPipelineBarrier)
VKF_FUNCTION_EXPORT(vkCmdBeginQuery)
VKF_FUNCTION_EXPORT(vkCmdEndQuery)
VKF_FUNCTION_EXPORT(vkCmdResetQueryPool)
VKF_FUNCTION_EXPORT(vkCmdWriteTimestamp)
VKF_FUNCTION_EXPORT(vkCmdCopyQueryPoolResults)
VKF_FUNCTION_EXPORT(vkCmdPushConstants)
VKF_FUNCTION_EXPORT(vkCmdBeginRenderPass)
VKF_FUNCTION_EXPORT(vkCmdNextSubpass)
VKF_FUNCTION_EXPORT(vkCmdEndRenderPass)
VKF_FUNCTION_EXPORT(vkCmdExecuteCommands)
#endif

// -----------------------------------------------------------------------------
// Vulkan 1.1
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkEnumerateInstanceVersion)
VKF_FUNCTION_EXPORT(vkBindBufferMemory2)
VKF_FUNCTION_EXPORT(vkBindImageMemory2)
VKF_FUNCTION_EXPORT(vkGetDeviceGroupPeerMemoryFeatures)
VKF_FUNCTION_EXPORT(vkCmdSetDeviceMask)
VKF_FUNCTION_EXPORT(vkCmdDispatchBase)
VKF_FUNCTION_EXPORT(vkEnumeratePhysicalDeviceGroups)
VKF_FUNCTION_EXPORT(vkGetImageMemoryRequirements2)
VKF_FUNCTION_EXPORT(vkGetBufferMemoryRequirements2)
VKF_FUNCTION_EXPORT(vkGetImageSparseMemoryRequirements2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFeatures2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceProperties2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFormatProperties2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceImageFormatProperties2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceQueueFamilyProperties2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceMemoryProperties2)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSparseImageFormatProperties2)
VKF_FUNCTION_EXPORT(vkTrimCommandPool)
VKF_FUNCTION_EXPORT(vkGetDeviceQueue2)
VKF_FUNCTION_EXPORT(vkCreateSamplerYcbcrConversion)
VKF_FUNCTION_EXPORT(vkDestroySamplerYcbcrConversion)
VKF_FUNCTION_EXPORT(vkCreateDescriptorUpdateTemplate)
VKF_FUNCTION_EXPORT(vkDestroyDescriptorUpdateTemplate)
VKF_FUNCTION_EXPORT(vkUpdateDescriptorSetWithTemplate)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceExternalBufferProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceExternalFenceProperties)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceExternalSemaphoreProperties)
VKF_FUNCTION_EXPORT(vkGetDescriptorSetLayoutSupport)
#endif

// -----------------------------------------------------------------------------
// KHR Swapchain
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkCreateSwapchainKHR)
VKF_FUNCTION_EXPORT(vkDestroySwapchainKHR)
VKF_FUNCTION_EXPORT(vkGetSwapchainImagesKHR)
VKF_FUNCTION_EXPORT(vkAcquireNextImageKHR)
VKF_FUNCTION_EXPORT(vkQueuePresentKHR)
VKF_FUNCTION_EXPORT(vkGetDeviceGroupPresentCapabilitiesKHR)
VKF_FUNCTION_EXPORT(vkGetDeviceGroupSurfacePresentModesKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDevicePresentRectanglesKHR)
VKF_FUNCTION_EXPORT(vkAcquireNextImage2KHR)
#endif

// -----------------------------------------------------------------------------
// KHR Surface
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkDestroySurfaceKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSurfaceSupportKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSurfaceFormatsKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSurfacePresentModesKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Display
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceDisplayPropertiesKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceDisplayPlanePropertiesKHR)
VKF_FUNCTION_EXPORT(vkGetDisplayPlaneSupportedDisplaysKHR)
VKF_FUNCTION_EXPORT(vkGetDisplayModePropertiesKHR)
VKF_FUNCTION_EXPORT(vkCreateDisplayModeKHR)
VKF_FUNCTION_EXPORT(vkGetDisplayPlaneCapabilitiesKHR)
VKF_FUNCTION_EXPORT(vkCreateDisplayPlaneSurfaceKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Display Swapchain
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkCreateSharedSwapchainsKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Multiview
//
#ifdef VK_NO_PROTOTYPES
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFeatures2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceProperties2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceFormatProperties2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceImageFormatProperties2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceQueueFamilyProperties2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceMemoryProperties2KHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceSparseImageFormatProperties2KHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xcb Surface
//
#if defined(VK_USE_PLATFORM_XCB_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateXcbSurfaceKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceXcbPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Xlib Surface
//
#if defined(VK_USE_PLATFORM_XLIB_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateXlibSurfaceKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceXlibPresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Win32 Surface
//
#if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateWin32SurfaceKHR)
VKF_FUNCTION_EXPORT(vkGetPhysicalDeviceWin32PresentationSupportKHR)
#endif

// -----------------------------------------------------------------------------
// KHR Android Surface
//
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateAndroidSurfaceKHR)
#endif

// -----------------------------------------------------------------------------
// KHR MacOS Surface
//
#if defined(VK_USE_PLATFORM_MACOS_MVK) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateMacOSSurfaceMVK)
#endif

// -----------------------------------------------------------------------------
// KHR IOS Surface
//
#if defined(VK_USE_PLATFORM_IOS_MVK) && defined(VK_NO_PROTOTYPES)
VKF_FUNCTION_EXPORT(vkCreateIOSSurfaceMVK)
#endif

namespace vkf {

	class Windows;
	class Instance;
	class Device;
	class Surface;
	class SwapChain;
	class RenderPass;
	class CommandBuffer;
	class Queue;
	class Semaphore;
	class Fence;
	class FenceManager;
	class UniformBuffer;
	class Texture;
	class Texture1D;
	class Texture2D;
	class Texture3D;
	class TextureCube;
	class TextureArray2D;
	class TextureSampler;
	class ShaderModule;
	class VertexShader;
	class FragmentShader;
	class TesselationControlShader;
	class TesselationEvaluationShader;
	class ComputeShader;

	extern void init();
	extern void destroy();

	extern const char* vkVkPresentModeKHRToString(VkPresentModeKHR presentMode);
	extern const char* vkVkPhysicalDeviceTypeToString(VkPhysicalDeviceType physicalDeviceType);
	extern const char* vkVkResultToString(VkResult result);
	extern VkResult showSupportedLayersAndExtensions();
	extern uint32_t getMemoryTypeIndex(VkPhysicalDeviceMemoryProperties deviceMemoryProperties, uint32_t typeBits, VkFlags properties);
	extern void setImageLayout(VkCommandBuffer cmdbuffer,
	                           VkImage image,
	                           VkImageAspectFlags aspectMask,
	                           VkImageLayout oldImageLayout,
	                           VkImageLayout newImageLayout);

	struct VulkanImage {
		VkImage image;
		VkDeviceMemory memory;
		VkImageView imageView;
	};

	class BufferStride {
		public:
			explicit BufferStride(uint32_t stride)
				: m_stride(stride) {
			}

			operator uint32_t() {
				return m_stride;
			}

			static BufferStride Zero;

		private:

			uint32_t m_stride;
	};

	class BufferSize {
		public:
			explicit BufferSize(uint32_t size)
				: m_size(size) {
			}

			operator uint32_t() {
				return m_size;
			}

			// TODO I don't like this but for now ...
			operator size_t() const {
				return m_size;
			}

			static BufferSize Zero;

		private:

			uint32_t m_size;
	};

	class BindingPoint {
		public:
			explicit BindingPoint(uint32_t size)
				: m_size(size) {
			}

			operator uint32_t() {
				return m_size;
			}

			operator uint32_t() const {
				return m_size;
			}

			static BindingPoint Zero;

		private:

			uint32_t m_size;
	};

	class LocationPoint {
		public:
			explicit LocationPoint(uint32_t size)
				: m_size(size) {
			}

			operator uint32_t() {
				return m_size;
			}

			operator uint32_t() const {
				return m_size;
			}

			static LocationPoint Zero;

		private:

			uint32_t m_size;
	};

	class FileName {
		public:
			FileName(const std::string& filename)
				: m_filename(filename) {

			}

			operator const char* () const {
				return m_filename.c_str();
			}

		private:

			std::string m_filename;
	};

	class ShaderSource {
		public:
			ShaderSource(const std::string& source)
				: m_source(source) {

			}

			uint32_t size() const {
				return (uint32_t)m_source.size();
			}

			uint32_t* data() const {
				return (uint32_t*)m_source.data();
			}

			operator const char* () const {
				return m_source.c_str();
			}

		private:

			std::string m_source;
	};

	/**
	 * @class Debug
	 * @brief Helper class for VkDebugReportCallbackEXT.
	 */
	class Debug {
		public:
			Debug(VkInstance instance);

			~Debug();

			VkResult init();

			static VKAPI_ATTR VkBool32 VKAPI_CALL myDebugReportCallback(VkDebugReportFlagsEXT flags,
			    VkDebugReportObjectTypeEXT objectType,
			    uint64_t object,
			    size_t location,
			    int32_t messageCode,
			    const char* pLayerPrefix,
			    const char* pMessage,
			    void* pUserData);

			operator VkDebugReportCallbackEXT() {
				return m_callback;
			}

		private:

			VkInstance m_instance;
			VkDebugReportCallbackEXT m_callback;

			PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
			PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
			PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
	};

	/**
	 * @class Instance
	 * @brief Helper class for VkInstance.
	 */
	class Instance {
		public:
			Instance(const std::string& title, uint32_t vulkanVersion = VK_MAKE_VERSION(1, 0, 0));
			~Instance();

			/// Initialize the Vulkan instance.
			VkResult init();

			/// Initialize this object using a already initialized VkInstance.
			VkResult init(VkInstance instance);

			/// Destroy the Vulkan instance.
			void destroy();

			/// Returns all physical devices.
			const std::vector<VkPhysicalDevice>& getPhysicalDevices() const;

			operator VkInstance() {
				return m_instance;
			}

		protected:

			VkResult postInit();

		private:

			VkInstance m_instance;
			std::string m_title;
			uint32_t m_version;
			Debug* m_debug;
			std::vector<VkPhysicalDevice> m_physicalDevices;
	};

	/**
	 * @class Device
	 * @brief Helper class for VkDevice.
	 */
	class Device {
		public:
			Device(Instance* instance, VkPhysicalDeviceType physicalDeviceType = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);

			~Device();

			/// Initialize the device.
			VkResult init();
			VkResult init(VkDevice device);

			/// Destroy the device.
			void destroy();

			/// Wait until device gets into idle state.
			VkResult waitIdle();

			/// Returns the Vulkan instance object.
			Instance* getInstance() const;

			/// Returns the device memory properties.
			VkPhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties() const;

			const std::vector<VkQueueFamilyProperties>& getQueueFamilyProperties() const;

			/// Returns the physical device assigned to this device.
			VkPhysicalDevice getPhysicalDevice() const;

			uint32_t getGraphicsQueueIndex() const;

			uint32_t getQueueIndex() const;

			operator VkDevice() {
				return m_device;
			}

		protected:

			VkResult preInit();

		private:

			// Holds the Vulkan instance.
			Instance* m_instance;

			// The handle for a physical device.
			VkPhysicalDevice m_physicalDevice;

			// Device handle.
			VkDevice m_device;

			// Holds the type of the physical device.
			VkPhysicalDeviceType m_physicalDeviceType;

			// Stores physical device properties (for e.g. checking device limits)
			VkPhysicalDeviceProperties m_deviceProperties;

			// Stores phyiscal device features (for e.g. checking if a feature is available)
			VkPhysicalDeviceFeatures m_deviceFeatures;

			// Holds the familiy queue index of this device.
			uint32_t m_graphicsQueueIndex;
			uint32_t m_maxGraphicsQueueCount;
			uint32_t m_queueIndex;

			std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;

			// Holds physical device memory properties.
			VkPhysicalDeviceMemoryProperties m_physicalDeviceMemoryProperties;
	};

	/**
	 * @class CommandPool
	 * @brief Helper class for the VkCommandPool.
	 */
	class CommandPool {
		public:
			CommandPool(Device* device, VkCommandPoolCreateFlags commandPoolCreateFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
			~CommandPool();

			/// Initialize the command pool.
			VkResult init();

			/// Resets the command pool.
			VkResult reset(VkCommandPoolCreateFlags commandPoolCreateFlags);

			/// Destroys the command pool.
			void destroy();

			/// Return the device assigned to the command pool.
			Device& getDevice() const;

			operator VkCommandPool() {
				return m_cmdPool;
			}

		public:
			Device* m_device;
			VkCommandPool m_cmdPool;
			VkCommandPoolCreateFlags m_commandPoolCreateFlags;
	};

	/**
	 * @class CommandBuffer
	 * @brief Helper class for the VkCommandBuffer.
	 */
	class CommandBuffer {
		public:
			CommandBuffer(CommandPool* commandPool);
			~CommandBuffer();

			/// Initialize command buffer.
			VkResult init();

			/// Destroy command buffer.
			void destroy();

			/// Begin recording into command buffer.
			VkResult begin();

			/// End recording into command buffer.
			VkResult end();

			void reset();

			operator VkCommandBuffer() {
				return m_cmdBuffer;
			}

			operator const VkCommandBuffer*() {
				return &m_cmdBuffer;
			}

		public:

			CommandPool* m_commandPool;
			VkCommandBuffer m_cmdBuffer;
			bool m_isBegin;
	};

	/**
	 * @class CommandBufferScope
	 * @brief
	 */
	class CommandBufferScope {
		public:
			CommandBufferScope(CommandBuffer* commandBuffer) : cmdBuffer(commandBuffer) {
				cmdBuffer->begin();
			}

			~CommandBufferScope() {
				cmdBuffer->end();
			}

		private:

			CommandBuffer* cmdBuffer;
	};

	/**
	 * @class CommandBuffers
	 * @brief Helper class for multiple CommandBuffer.
	 */
	class CommandBuffers {
		public:
			CommandBuffers(Device* device, CommandPool* commandPool, uint32_t number);
			~CommandBuffers();

			/// Initialize the command buffers.
			VkResult init();

			/// Destroy the command buffers.
			void destroy();

			/// Returns the command buffers array.
			const std::vector<CommandBuffer*>& getCommandBuffers() const;

			CommandBuffer* getCommandBuffer(int index) const {
				return m_cmdBuffers[index];
			}

			inline CommandBuffer* operator[](int index) {
				return m_cmdBuffers[index];
			}

			inline uint32_t getNumber() const {
				return m_cmdBuffers.size();
			}

		public:

			Device* m_device;
			CommandPool* m_commandPool;
			CommandBuffer* m_postPresentCmdBuffer;
			std::vector<CommandBuffer*> m_cmdBuffers;
	};

	/**
	 * @class Semaphore
	 * @brief Helper class for VkSemaphore.
	 */
	class Semaphore {
		public:
			Semaphore(Device* device);

			~Semaphore();

			/// Initialize semaphore.
			VkResult init();

			/// Destroy semaphore.
			void destroy();

			operator VkSemaphore() {
				return m_semaphore;
			}

			operator const VkSemaphore*() {
				return &m_semaphore;
			}

		private:

			Device* m_device;
			VkSemaphore m_semaphore;
	};

	/**
	 * @struct Fence
	 * @brief Helper struct for VkFence.
	 */
	class Fence {
		public:
			friend class FenceManager;

			Fence(Device* device);

			void reset();

			operator VkFence() {
				return m_fence;
			}

			operator const VkFence* () {
				return &m_fence;
			}

		protected:

			/// Initialize the fence.
			VkResult init();

			/// Destroy the fence.
			void destroy();

		private:

			Device* m_device;
			VkFence m_fence;
	};

	class FenceManager {
		public:
			FenceManager(Device* device);

			/// Initialize the manager.
			VkResult init();

			/// Destroy the manager.
			void destroy();

			/// Add a new fence to the system.
			VkResult add(Fence& fence);

			/// Removes the fence from the system.
			void remove(Fence& fence);

			/// Reset one specific fence.
			void reset(Fence& fence);

			/// Reset all fences.
			void resetAll();

			/// Returns the state of the fence.
			VkResult getStatus(Fence& fence);

			/// Wait for fences.
			VkResult waitForAllFences();

		private:

			Device* m_device;
			std::vector<Fence> m_fences;
	};

	/**
	 * @class Queue
	 * @brief Helper class for VkQueue.
	 */
	class Queue {
		public:
			Queue(Device* device, uint32_t famliyQueueIndex, uint32_t queueIndex);

			/// Initialize queue.
			VkResult init();

			VkResult submit(VkSubmitInfo& submitInfo);

			VkResult submit(CommandBuffer* commandBuffer);

			/// Submit command buffer.
			VkResult submit(CommandBuffer* commandBuffer, VkPipelineStageFlags pipelineStageFlags);

			/// Submit command buffer with a specified fence.
			VkResult submit(CommandBuffer* commandBuffer, VkPipelineStageFlags pipelineStageFlags, Semaphore* renderComplete, Semaphore* presentComplete);

			/// Wait until idle state.
			VkResult waitIdle();

			/// Returns the queue family index.
			uint32_t getQueueFamilyIndex() const;

			void destroy();

			operator VkQueue() {
				return m_queue;
			}

		private:

			Device* m_device;
			VkQueue m_queue;
			uint32_t m_queueFamilyIndex;
			uint32_t m_queueIndex;
	};

	/**
	 * @class Surface
	 * @brief Helper class for VkSurfaceKHR.
	 */
	class Surface {
		public:
			Surface(Device* device, Windows* window);
			~Surface();

			typedef void* SurfaceType;

			/// Initialize surface.
			VkResult init();

			/// Create surface.
			VkResult create(Windows& window);

			/// Returns the device assigned to this surface.
			Device& getDevice() const;

			/// Returns the queue famliy index used for this surface.
			uint32_t getQueueFamilyIndex() const;

			/// Returns the queue index.
			uint32_t getQueueIndex() const;

			/// Destroy this surface.
			void destroy();

			/// Returns the surface capabilities.
			VkSurfaceCapabilitiesKHR getSurfaceCaps() const;

			/// Returns the present mode count.
			uint32_t getPresentModeCount() const;

			/// Returns the present mode.
			VkPresentModeKHR getPresentMode() const;

			/// Returns the color format supported by this surface.
			VkFormat getColorFormat() const;

			/// Returns the supported color space.
			VkColorSpaceKHR getColorSpace() const;

			/// Returns the extend2D of this surface.
			VkExtent2D getExtent2D() const;

			operator VkSurfaceKHR() {
				return m_surface;
			}

		private:

			Device* m_device;
			Windows* m_window;
			VkSurfaceKHR m_surface;
			VkSurfaceCapabilitiesKHR m_surfCaps;
			uint32_t m_presentModeCount;
			VkPresentModeKHR m_presentMode;
			uint32_t m_queueFamilyIndex;
			uint32_t m_queueIndex;

			VkFormat m_colorFormat;
			VkColorSpaceKHR m_colorSpace;
			VkExtent2D m_extent2D;
	};

	/**
	 * @class RenderPass
	 * @brief Helper class for VkRenderPass.
	 */
	class RenderPass {
		public:
			RenderPass(Device* device);
			~RenderPass();

			/// Initialize render pass.
			VkResult init();

			/// Destroy render pass.
			void destroy();

			void addColorAttachment(VkFormat format, VkImageLayout initialImageLayout, VkImageLayout finalImageLayout);
			void addDepthStencilAttachment(VkFormat format, VkImageLayout initialImageLayout = VK_IMAGE_LAYOUT_UNDEFINED);

			operator VkRenderPass() {
				return m_renderPass;
			}

		private:

			Device* m_device;
			VkRenderPass m_renderPass;
			std::vector<VkAttachmentDescription> m_colorAttachments;
			std::vector<VkAttachmentDescription> m_depthStencilAttachment;
			bool m_swapChainRenderPass;
	};

	class RenderPassScope {
		public:
			RenderPassScope(CommandBuffer* commandBuffer, SwapChain* swapChain, uint32_t currentBuffer, std::array<VkClearValue, 2>& clearValues);
			~RenderPassScope();
		private:
			CommandBuffer* m_commandBuffer;
	};

	/**
	 * @class SwapChain
	 * @brief Helper class for VkSwapchainKHR.
	 */
	class SwapChain {
		public:
			SwapChain(Surface* surface);
			~SwapChain();

			/**
			 * @class ColorAttachment
			 * @brief Holds resource information for a SwapChain framebuffer.
			 */
			struct SwapChainImages {
				VkImage image;
				VkImageView imageView;
			};

			/// Initialize the SwapChain.
			VkResult init();

			/// Create the framebuffers for the SwapChain images.
			VkResult createFramebuffers(RenderPass& renderPass);

			/// Create depth/stencil attachment.
			VkResult setupDepthStencil();

			/// Returns the next image in the SwapChain that needs to be handled.
			VkResult nextImage(uint32_t& imageIndices, Semaphore* presentSemaphore);

			/// Present the image.
			VkResult present(Queue* queue, uint32_t imageIndices, Semaphore* renderingFinishedSemaphore);

			/// Destroy the SwapChain.
			void destroy();

			/// Returns the number of SwapChain framebuffers.
			uint32_t getImageCount();

			/// Returns the specified Swap Chain Image.
			VkImage getImage(uint32_t idx) const;

			/// Returns the specified Swap Chain Framebuffer.
			VkFramebuffer getFramebuffer(uint32_t idx) const;

			/// Returns the array of SwapChain framebuffers.
			std::vector<SwapChainImages>& getSwapImages();

			VkSwapchainCreateInfoKHR getSwapchainCreateInfo() const;

			/// Returns the associated Surface.
			Surface* getSurface() const;

			VkSemaphore getPresentCompleteSemaphore() const;
			VkSemaphore getRenderCompleteSemaphore() const;
			RenderPass& getRenderPass() const;

			inline VkExtent2D getExtent2D() {
				return m_surface->getExtent2D();
			}

			operator VkSwapchainKHR() {
				return m_swapChain;
			}

			operator const VkSwapchainKHR*() {
				return &m_swapChain;
			}

		private:

			Surface* m_surface;
			RenderPass* m_renderPass;
			VkSwapchainKHR m_swapChain;
			VkSwapchainKHR m_oldSwapchain;

			VkSwapchainCreateInfoKHR m_swapchainCreateInfo;
			std::vector<SwapChainImages> m_swapChainBuffers;
			std::vector<VkFramebuffer> m_frameBuffers;
			VkFormat m_depthStencilFormat;
			VulkanImage m_depthStencilImage;

			VkFence m_fence;
	};

	/**
	 * @class FrameBuffer
	 * @brief Helper class for VkFramebuffer.
	 */
	class FrameBuffer {
		public:
			FrameBuffer(Device* device, RenderPass* renderPass);

			struct ColorAttachment {
				ColorAttachment() : image(VK_NULL_HANDLE), memory(VK_NULL_HANDLE), imageView(VK_NULL_HANDLE) {}
				VkImage image;
				VkDeviceMemory memory;
				VkImageView imageView;
			};

			struct DepthStencil {
				DepthStencil() : image(VK_NULL_HANDLE), memory(VK_NULL_HANDLE), imageView(VK_NULL_HANDLE) {}
				VkImage image;
				VkDeviceMemory memory;
				VkImageView imageView;
			};

			VkResult init();
			VkResult create();
			VkResult addColor(SwapChain* swapChain);
			VkResult addDepthStencil(VkFormat format, uint32_t width, uint32_t height);

			operator VkFramebuffer() {
				return m_frameBuffer;
			}

		private:

			Device* m_device;
			RenderPass* m_renderPass;

			VkFramebuffer m_frameBuffer;
			DepthStencil m_depthStencil;

			std::vector<VkImageView> m_colorAttachments;
			Texture2D* m_depthStencilAttachment;
			uint32_t m_width;
			uint32_t m_height;
			bool m_swapChainDefinition;
	};

	/**
	 * @class BufferBase
	 * @brief Helper class for basic buffer handling.
	 */
	class BufferBase {
		public:
			BufferBase(Device* device, VkBufferUsageFlagBits bufferUsageFlagBits, const BufferSize& size = BufferSize::Zero);
			virtual ~BufferBase();

			VkResult init();
			void destroy();
			void* map();
			void unmap();
			int upload(uint8_t* src, const BufferSize& size, uint64_t offset = 0);

			BufferBase& setSize(const BufferSize& size);

			operator VkBuffer() {
				return m_buffer;
			}

			operator VkBuffer*() {
				return &m_buffer;
			}

		protected:

			Device* m_device;
			VkBufferUsageFlagBits m_bufferUsageFlagBits;
			VkBuffer m_buffer;
			VkDeviceMemory m_memory;
			VkMemoryAllocateInfo m_memoryAllocateInfo;
			VkMemoryRequirements m_memoryRequirements;
			BufferSize m_size;
			bool m_initialized;
	};

	/**
	 * @class VertexBuffer
	 * @brief Helper class for vertex buffer.
	 */
	class VertexBuffer : public BufferBase {
		public:
			explicit VertexBuffer(Device* device, const BufferSize& size, BufferStride stride = BufferStride::Zero);

			uint32_t getBindingID() const;
			BufferStride getStride() const;
			VertexBuffer& addElement(const BindingPoint& binding, const LocationPoint& location, VkFormat format, uint32_t offset);
			const std::vector<VkVertexInputAttributeDescription>& getVertexInputAttributeDescription() const;

		private:

			uint32_t m_bidingID;
			BufferStride m_stride;
			std::vector<VkVertexInputAttributeDescription> m_vertexInputAttributeDescription;
	};

	/**
	 * @class IndexBuffer
	 * @brief Helper class for index buffer.
	 */
	class IndexBuffer : public BufferBase {
		public:
			explicit IndexBuffer(Device* device, uint32_t numberOfIndicies, const BufferSize& size = BufferSize::Zero);
			uint32_t getNumberOfIndicies() const;

		private:

			uint32_t m_number;
	};


	/**
	 * @class UniformBuffer
	 * @brief Helper class for uniform buffer.
	 */
	class UniformBuffer : public BufferBase {
		public:
			explicit UniformBuffer(Device* device, const BufferSize& size = BufferSize::Zero);
			VkDescriptorBufferInfo& getDescriptorBufferInfo();

		private:

			VkDescriptorBufferInfo descriptorBufferInfo;
	};

	/**
	 * @class StagingBuffer
	 * @brief This buffers memory will reside in the host side and will be used to copy data to GPU memory.
	 */
	class StagingBuffer : public BufferBase {
		public:
			explicit StagingBuffer(Device* device, const BufferSize& size = BufferSize::Zero);
	};

	/**
	 * @class DescriptorSetLayout
	 * @brief Helper class for VkDescriptorSetLayout.
	 */
	class DescriptorSetLayout {
		public:
			DescriptorSetLayout(Device* device);

			DescriptorSetLayout& add(const BindingPoint& binding, VkDescriptorType descriptorType, VkShaderStageFlags shaderStageFlags);

			VkResult init();

			void destroy();

			operator const VkDescriptorSetLayout*() {
				return &m_descriptorSetLayout;
			}

			operator VkDescriptorSetLayout() {
				return m_descriptorSetLayout;
			}

		private:

			Device* m_device;
			VkDescriptorSetLayout m_descriptorSetLayout;
			std::vector<VkDescriptorSetLayoutBinding> m_bindings;
	};

	/**
	 * @class DescriptorPool
	 * @brief Helper class for VkDescriptorPool.
	 */
	class DescriptorPool {
		public:
			DescriptorPool(Device* device);

			DescriptorPool& add(VkDescriptorType descriptorType, uint32_t count = 1);

			VkResult init();

			void destroy();

			operator VkDescriptorPool() {
				return m_descriptorPool;
			}

		private:

			Device* m_device;
			VkDescriptorPool m_descriptorPool;
			std::vector<VkDescriptorPoolSize> m_types;
	};

	/**
	 * @class DescriptorSet
	 * @brief Helper class for VkDescriptorSet.
	 */
	class DescriptorSet {
		public:
			DescriptorSet(Device* device, DescriptorPool* descriptorPool, DescriptorSetLayout* layout);

			void bind(const BindingPoint& binding, UniformBuffer* uniformBuffer);
			void bind(const BindingPoint& binding, Texture* texture, TextureSampler* textureSample);

			/// Initialize descriptor set.
			VkResult init();

			/// Destroys the descriptor set.
			void destroy();

			operator VkDescriptorSet() {
				return m_descriptorSet;
			}

			operator const VkDescriptorSet*() {
				return &m_descriptorSet;
			}
		private:

			Device* m_device;
			DescriptorPool* m_descriptorPool;
			DescriptorSetLayout* m_layout;
			VkDescriptorSet m_descriptorSet;
			std::vector<VkWriteDescriptorSet> m_writeDescriptorSets;
			std::map<uint32_t, VkDescriptorBufferInfo> m_descriptorBufferInfo;
			std::map<uint32_t, VkDescriptorImageInfo> m_descriptorImageInfo;
	};

	/**
	 * @class PipelineCache
	 * @brief
	 */
	class PipelineCache {
		public:
			PipelineCache(Device* device);

			~PipelineCache();

			VkResult init();

			void destroy();

			operator VkPipelineCache() {
				return m_pipeLineCache;
			}

		private:

			Device* m_device;
			VkPipelineCache m_pipeLineCache;
	};

	/**
	 * @class ShaderModule
	 * @brief Helper class for VkShaderModule.
	 */
	class ShaderModule {
		public:
			ShaderModule(Device* device, VkShaderStageFlagBits shaderStageFalgBits, const std::string& entryName = "main");
			~ShaderModule();

			/// Load the shader source.
			bool load(const FileName& filename);

			/// Destroy the shader.
			void destroy();

			VkShaderStageFlagBits getShaderStageFlagBits() const;

			const char* getName() const;

			operator VkShaderModule() {
				return m_shaderModule;
			}

			operator VkShaderModule*() {
				return &m_shaderModule;
			}

		private:

			Device* m_device;
			VkShaderModule m_shaderModule;
			VkShaderStageFlagBits m_shaderStageFlagBits;
			std::string m_name;
	};

	/**
	 * @class VertexShader
	 * @brief
	 */
	class VertexShader : public ShaderModule {
		public:
			VertexShader(Device* device);
	};

	/**
	 * @class GeometryShader
	 * @brief
	 */
	class GeometryShader : public ShaderModule {
		public:
			GeometryShader(Device* device);
	};

	/**
	 * @class FragmentShader
	 * @brief
	 */
	class FragmentShader : public ShaderModule {
		public:
			FragmentShader(Device* device);
	};

	/**
	 * @class TesselationControlShader
	 * @brief
	 */
	class TesselationControlShader : public ShaderModule {
		public:
			TesselationControlShader(Device* device);
	};

	/**
	 * @class TesselationEvaluationShader
	 * @brief
	 */
	class TesselationEvaluationShader : public ShaderModule {
		public:
			TesselationEvaluationShader(Device* device);
	};

	/**
	 * @class ComputeShader
	 * @brief
	 */
	class ComputeShader : public ShaderModule {
		public:
			ComputeShader(Device* device);
	};

	/**
	 * @class Texture
	 * @brief Base class for textures.
	 *
	 * All texture memory will be located on the GPU device.
	 */
	class Texture {
		public:
			Texture(Device* device);
			Texture(Device* device,
			        VkImageLayout imageTextureLayout,
			        VkImageType imageType,
			        VkImageViewType imageViewType,
			        VkFormat format,
			        uint32_t width,
			        uint32_t height,
			        uint32_t depth = 1);
			~Texture();

			VkResult init();
			VkResult init(VkImageLayout imageTextureLayout,
			              VkImageType imageType,
			              VkImageViewType imageViewType,
			              VkFormat format,
			              uint32_t width,
			              uint32_t height,
			              uint32_t depth = 1);
			void destroy();
			void* map();
			void unmap();
			VkResult upload(uint8_t* src, const BufferSize& size, uint64_t offset = 0);
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			size_t getSize();
			VkFormat getFormat() const;
			VkImage getImage() const;
			VkImageView getImageView() const;
			VkImageLayout getImageLayout() const;

		private:

			Device* m_device;
			VkImage m_image;
			VkImageView m_imageView;
			VkSampler m_sampler;
			VkImageType m_imageType;
			VkImageViewType m_imageViewType;
			VkFormat m_format;
			VkImageLayout m_imageLayout;
			VkMemoryAllocateInfo m_memoryAllocateInfo;
			VkDeviceMemory m_memory;
			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_depth;
			VkMemoryRequirements m_memoryRequirements;
	};

	class Texture1D : public Texture {
		public:
			Texture1D(Device* device, VkFormat format, uint32_t width, uint32_t height)
				: Texture(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TYPE_1D, VK_IMAGE_VIEW_TYPE_1D, format, width, height, 1) {

			}
	};

	class Texture2D : public Texture {
		public:
			Texture2D(Device* device, VkFormat format, uint32_t width, uint32_t height)
				: Texture(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D, format, width, height, 1) {

			}
	};

	class Texture3D : public Texture {
		public:
			Texture3D(Device* device, VkFormat format, uint32_t width, uint32_t height, uint32_t depth)
				: Texture(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TYPE_3D, VK_IMAGE_VIEW_TYPE_3D, format, width, height, depth) {

			}
	};

	class TextureCube : public Texture {
		public:
			TextureCube(Device* device, VkFormat format, uint32_t width, uint32_t height)
				: Texture(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_CUBE, format, width, height, 6) {

			}
	};

	class TextureArray2D : public Texture {
		public:
			TextureArray2D(Device* device, VkFormat format, uint32_t width, uint32_t height, uint32_t depth)
				: Texture(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TYPE_2D, VK_IMAGE_VIEW_TYPE_2D_ARRAY, format, width, height) {

			}
	};


	class TextureSampler {
		public:
			TextureSampler(Device* device);

			VkResult init();
			void destroy();

			TextureSampler& setMinFilter(VkFilter minFilter);
			TextureSampler& setMagFilter(VkFilter magFilter);
			TextureSampler& setAddressModeU(VkSamplerAddressMode U);
			TextureSampler& setAddressModeV(VkSamplerAddressMode V);
			TextureSampler& setAddressModeW(VkSamplerAddressMode W);

			operator VkSampler() {
				return m_textureSampler;
			}

		private:

			Device* m_device;
			VkSampler m_textureSampler;
			VkSamplerCreateInfo m_samplerCreateInfo;
	};

	/**
	 * @class Pipeline
	 * @brief Helper class for VkPipeline.
	 */

	class Pipeline {
		public:
			Pipeline(Device* device, DescriptorSetLayout* descriptorSetLayout, RenderPass* renderPass, VkExtent2D extent2D);
			~Pipeline();

			VkResult init();
			void destroy();

			void addVertexState(VertexBuffer* vertexBuffer);
			void addIndexState(IndexBuffer* indexBuffer);
			void addShaderModule(ShaderModule* shaderModule);

			Pipeline& setUsedTopology(VkPrimitiveTopology primitiveTopology);
			Pipeline& setFrontFace(VkFrontFace frontFace);
			Pipeline& setEnableDepthStencil(VkBool32 enable);

			VkPipelineLayout getPipelineLayout() const;

			Pipeline& setCullMode(VkCullModeFlags cullModeFlags);

			operator VkPipeline() {
				return m_pipeline;
			}

		private:

			Device* m_device;
			DescriptorSetLayout* m_descriptorSetLayout;
			RenderPass* m_renderPass;
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;

			VkPipelineVertexInputStateCreateInfo m_pipelineVertexInputStateCreateInfo;
			VkPipelineInputAssemblyStateCreateInfo m_inputAssemblyState;
			std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;
			VkVertexInputBindingDescription m_vertexInputBindingDescription;
			VkExtent2D m_extent2D;
			std::vector<VkViewport> m_viewports;
			std::vector<VkRect2D> m_scissors;
			VkPipelineRasterizationStateCreateInfo m_rasterizationStateCreateInfo;
			VkPipelineDepthStencilStateCreateInfo m_depthStencilState;
	};

}

#ifdef VKF_USE_INLINED_DEFINITION
#include "vulkan_framework.cpp"
#endif

#endif
