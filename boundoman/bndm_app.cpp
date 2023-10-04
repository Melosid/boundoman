#include "bndm_app.hpp"

namespace bndm {
	BndmApp::BndmApp() {}
	BndmApp::~BndmApp() {}

	void BndmApp::run() {
        createSyncObjects();
		mainLoop();
		cleanup();
	}

	void BndmApp::mainLoop() {
		while (!bndmWindow.shouldClose()) {
			glfwPollEvents();
            drawFrame();
		}

        vkDeviceWaitIdle(bndmDevice.getDevice());
	}

    void BndmApp::createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(bndmDevice.getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(bndmDevice.getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(bndmDevice.getDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }

    void BndmApp::drawFrame() {
        vkWaitForFences(bndmDevice.getDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        vkResetFences(bndmDevice.getDevice(), 1, &inFlightFences[currentFrame]);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(bndmDevice.getDevice(), *bndmSwapChain.getSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer((*bndmPipeline.getCommandBuffer())[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
        bndmPipeline.recordCommandBuffer((*bndmPipeline.getCommandBuffer())[currentFrame], imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &(*bndmPipeline.getCommandBuffer())[currentFrame];

        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(*bndmDevice.getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { *bndmSwapChain.getSwapChain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(*bndmDevice.getPresentQueue(), &presentInfo);

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

	void BndmApp::cleanup() {
		bndmPipeline.destroyFrameBuffers();
		bndmPipeline.destroyPipeline();
		bndmPipeline.destroyPipelineLayout();
		bndmPipeline.destroyRenderPass();
		bndmSwapChain.destroyImageViews();
		bndmSwapChain.destroySwapChain();
		bndmDevice.destroyDevice();
		bndmDevice.destroySurface();
		bndmInstance.destroyInstance();
		bndmWindow.destroyWindow();
	}
}