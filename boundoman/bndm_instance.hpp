#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

namespace bndm {
	class BndmInstance {
	public: 
#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif

		BndmInstance();
		~BndmInstance();

		BndmInstance(const BndmInstance&) = delete;
		BndmInstance& operator=(const BndmInstance&) = delete;

		VkInstance getVkInstance() const { return instance; };
		void createInstance();
		void setupDebugMessenger();

		bool getEnableValidationLayers() {
			return enableValidationLayers;
		}
		std::vector<const char*> getValidationLayers() {
			return validationLayers;
		}

		void destroyInstance();

	private: 
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
}