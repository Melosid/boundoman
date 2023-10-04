#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "bndm_device.hpp"
#include <iostream>

#include <vector>

namespace bndm {
	class BndmSwapChain {
	public:

		BndmSwapChain(BndmDevice& deviceRef, GLFWwindow* windowArg);
		~BndmSwapChain();

		BndmSwapChain(const BndmSwapChain&) = delete;
		BndmSwapChain& operator=(const BndmSwapChain&) = delete;

		void destroySwapChain();
		void destroyImageViews();

		VkFormat getSwapChainImageFormat() {
			return swapChainImageFormat;
		}

		VkSwapchainKHR* getSwapChain() {
			return &swapChain;
		}
		
		std::vector<VkFramebuffer>* getSwapChainFramebuffers() {
			return &swapChainFramebuffers;
		}

		std::vector<VkImageView>* getSwapChainImageViews() {
			return &swapChainImageViews;
		}

		VkExtent2D* getSwapChainExtent() {
			return &swapChainExtent;
		}

		std::vector<VkFramebuffer> resizeSwapChainFramebuffersVector(size_t n) {
			swapChainFramebuffers.resize(n);
			return swapChainFramebuffers;
		}

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(
			const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(
			const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void createSwapChain();
		void createImageViews();

		BndmDevice& device;
		GLFWwindow* window;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFramebuffers;
	};
}