#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "bndm_swap_chain.hpp"

#include <string>

namespace bndm {
	class BndmPipeline
	{
	public:
		const int MAX_FRAMES_IN_FLIGHT = 2;

		BndmPipeline(BndmDevice& device, BndmSwapChain& swapChain);
		~BndmPipeline();

		BndmPipeline(const BndmPipeline&) = delete;
		BndmPipeline& operator=(const BndmPipeline&) = delete;

		void destroyPipelineLayout();

		void destroyRenderPass();

		void destroyPipeline();

		void destroyFrameBuffers();

		void destroyCommandPool();

		void destroyCommandBuffer();

		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		std::vector<VkCommandBuffer>* getCommandBuffer() {
			return &commandBuffers;
		}

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline();

		void createRenderPass();

		void createFramebuffers();

		void createCommandPool();
		
		void createCommandBuffer();

		VkShaderModule createShaderModule(const std::vector<char>& code);

		BndmDevice& device;

		BndmSwapChain& swapChain;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}