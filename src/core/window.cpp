#include "window.h"


//window callback functions
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

bool Window::CreateWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //assigned glfw window handle and tell it how to delete when done
    windowPtr.reset(glfwCreateWindow(windowWidth, windowHeight, "plug", nullptr, nullptr),[](GLFWwindow* ptr){glfwDestroyWindow(ptr);});

    if(!windowPtr){
        static_assert(true, "Window Ptr Is Not Found");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(windowPtr.get());
    glfwSetFramebufferSizeCallback(windowPtr.get(), frameBufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        static_assert(true, "Failed to initialize glad");
        return false;
    }

    return true;
}

void Window::DestroyWindow() {
    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}