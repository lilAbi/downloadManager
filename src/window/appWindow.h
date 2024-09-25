

#ifndef DOWNLOADMANAGER_APPWINDOW_H
#define DOWNLOADMANAGER_APPWINDOW_H


//wrapper around a glfw class
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include <memory>


static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

//todo: this class will attempt to destroy the
class AppWindow {
private:
    struct GLFWDestructor{
        void operator()(GLFWwindow* ptr){
            spdlog::info("Deleting GLFWwindow using custom deleter");
            glfwDestroyWindow(ptr);
        }
    };

public:
    bool init();
    std::shared_ptr<GLFWwindow> getWindowPtr(){return windowPtr;}
    void setWindowSize(int w, int h) {};
    void setMousePosition(float x, float y) {};

public:
#ifdef __APPLE__
    int width{1920/2}, height{1080/2};
#else
    int width{1920}, height{1080};
#endif
    std::shared_ptr<GLFWwindow> windowPtr;
};


#endif //DOWNLOADMANAGER_APPWINDOW_H