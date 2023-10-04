#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace bndm {

	class BndmWindow {
	public:
		BndmWindow(int w, int h, std::string name);
		~BndmWindow();

		BndmWindow(const BndmWindow&) = delete;
		BndmWindow& operator=(const BndmWindow&) = delete;

		bool shouldClose() {
			return glfwWindowShouldClose(window);
		}

		void initWindow();
		void destroyWindow();

		GLFWwindow* getGLFWwindow() const { return window; }


	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
}