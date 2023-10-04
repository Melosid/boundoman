#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>
#include <iostream>

namespace bndm {
	
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class BndmDevice {
	public: 
		BndmDevice(VkInstance& instance, bool enableValidationLayers, std::vector<const char*> validationLayers, GLFWwindow* window);
		~BndmDevice();

		// Not copyable or movable
		BndmDevice(const BndmDevice&) = delete;
		BndmDevice& operator=(const BndmDevice&) = delete;
		BndmDevice(BndmDevice&&) = delete;
		BndmDevice& operator=(BndmDevice&&) = delete;

		VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }
		VkDevice getDevice() { 
			//std::cout << device << std::endl;
			return device; 
		}
		VkSurfaceKHR getSurface() { return surface; }
		
		void pickPhysicalDevice();
		void createLogicalDevice();
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		void destroyDevice();

		void createSurface();

		void destroySurface();
		
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		VkQueue* getGraphicsQueue() {
			return &graphicsQueue;
		}

		VkQueue* getPresentQueue() {
			return &presentQueue;
		}

	private:
		bool isDeviceSuitable(VkPhysicalDevice device);

		VkInstance instance;
		GLFWwindow* window;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkSurfaceKHR surface;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		bool enableValidationLayers;
		std::vector<const char*> validationLayers;

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};
}