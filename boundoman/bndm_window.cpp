#include "bndm_window.hpp"

namespace bndm {
    BndmWindow::BndmWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
        initWindow();
    };
    BndmWindow::~BndmWindow() {};

    void BndmWindow::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    };

    void BndmWindow::destroyWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    };

    void BndmWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto bndmWindow = reinterpret_cast<BndmWindow*>(glfwGetWindowUserPointer(window));
        bndmWindow->width = width;
        bndmWindow->height = height;
        bndmWindow->framebufferResized = true;
    };
}
