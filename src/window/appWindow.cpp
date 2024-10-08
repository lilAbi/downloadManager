#include "appWindow.h"

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height){
    if(auto* handle{reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window))}; handle){
        //spdlog::critical("framebuffer width {} height {}", width, height);

        if(handle->framebufferWidth > width || handle->framebufferHeight > height){
            spdlog::critical("framebuffer default");
            glViewport(0, 0, handle->framebufferWidth, handle->framebufferHeight);
        } else {
            spdlog::critical("framebuffer size width {} height {}", width, height);
            spdlog::critical("framebuffer basic");
            glViewport(0, 0, width, height);
        }

    }
}

static void AppWindowSizeCallback(GLFWwindow* window, int width, int height){
    if(auto* handle{reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window))}; handle){
        spdlog::critical("window width {} height {}", width, height);

        if(width < 1920/2 || height < 1080/2){
            glfwSetWindowSize(window, 1920/2, 1080/2);
        }

        handle->setWindowSize(width, height);

        //call a redraw
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
    glfwSetWindowSizeCallback(windowPtr.get(), AppWindowSizeCallback);
    //glfwSetInputMode(windowPtr.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwGetFramebufferSize(windowPtr.get(), &framebufferWidth, &framebufferHeight);
    spdlog::info("starting framebuffer size width {} height {}", framebufferWidth, framebufferHeight);

    //initialize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::info("Failed to initialize GLAD");
        return false;
    }

    //take a copy of the event manager pointer
    return true;
}

