#include "appWindow.h"

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height){
    if(auto* handle{reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window))}; handle){
        handle->setWindowSize(width, height);
        glViewport(0, 0, width, height);
    }
}

static void CursorPosCallback(GLFWwindow* window, double xposIn, double yposIn){
    if(auto* handle{reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window))}; handle){
        handle->setMousePosition(static_cast<float>(xposIn), static_cast<float>(yposIn));
    }
}

bool AppWindow::init() {
    //initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    windowPtr.reset(glfwCreateWindow(width, height, "download manager (beta)", nullptr, nullptr), GLFWDestructor());

    //test window creation
    if(!windowPtr){
        spdlog::info("Failed to create window");
        glfwTerminate();
        return false;
    }

    //set context/UserPointer & any callbacks
    glfwMakeContextCurrent(windowPtr.get());
    glfwSetWindowUserPointer(windowPtr.get(), reinterpret_cast<void*>(this));
    glfwSetFramebufferSizeCallback(windowPtr.get(), FrameBufferSizeCallback);
    glfwSetCursorPosCallback(windowPtr.get(), CursorPosCallback);

    //glfwSetInputMode(windowPtr.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //initialize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::info("Failed to initialize GLAD");
        return false;
    }

    //take a copy of the event manager pointer
    return true;
}

