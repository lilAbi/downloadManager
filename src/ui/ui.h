#ifndef DOWNLOADMANAGER_UI_H
#define DOWNLOADMANAGER_UI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include <tuple>

class Ui {
public:
    Ui() = default;
    //initialize any ui subsystem
    bool init(GLFWwindow* glfwWindowPtr);
    //imgui new frame internal setup
    void startUIFrame();
    //actual drawing logic
    void drawUi(std::pair<int,int> screenSize);
    //submit our ui data to gpu
    void endUIFrame();
    //clean up imgui stuff
    void cleanUp();
private:
    void drawBackground();
    void drawToolbar();


};


#endif //DOWNLOADMANAGER_UI_H
