#include "window.h"


//window callback functions
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

bool Window::CreateWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //assigned glfw window handle and tell it how to delete when done
    windowPtr.reset(glfwCreateWindow(windowWidth, windowHeight, "Electrical Retrieval", nullptr, nullptr),[](GLFWwindow* ptr){glfwDestroyWindow(ptr);});

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

    //A UserData field is a fairly common paradigm in C APIs that lets the user access
    //contextual data from within callbacks without needing to make everything global
    glfwSetWindowUserPointer(windowPtr.get(), reinterpret_cast<void *>(this));  //set the user pointer to this window instance

    return true;
}

void Window::DestroyWindow() {
    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

    //extract
    if(Window* windowHandler{reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))}; windowHandler) {
        windowHandler->windowHeight = height;
        windowHandler->windowWidth = width;
    }
}