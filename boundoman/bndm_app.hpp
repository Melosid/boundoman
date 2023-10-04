#include "bndm_window.hpp"
#include "bndm_instance.hpp"
#include "bndm_pipeline.hpp"

namespace bndm {
	class BndmApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		const int MAX_FRAMES_IN_FLIGHT = 2;

		BndmApp();
		~BndmApp();

		BndmApp(const BndmApp&) = delete;
		BndmApp& operator=(const BndmApp&) = delete;

		void run();
		void mainLoop();
		void cleanup();

		void createSyncObjects();

		void drawFrame();

	private:
		BndmWindow bndmWindow { WIDTH, HEIGHT, "Vulkan Tutorial" };
		GLFWwindow* window = bndmWindow.getGLFWwindow();

		BndmInstance bndmInstance{};
		VkInstance instance = bndmInstance.getVkInstance();
		
		BndmDevice bndmDevice{ instance, bndmInstance.getEnableValidationLayers(), bndmInstance.getValidationLayers(), window };
		BndmSwapChain bndmSwapChain{ bndmDevice, window };
		BndmPipeline bndmPipeline{ bndmDevice, bndmSwapChain };

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		uint32_t currentFrame = 0;
	};
}