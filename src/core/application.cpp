#include "application.h"

bool Application::init() {
    spdlog::info("Starting Application Initialization");

    //initialize window
    spdlog::info("Starting Window Initialization");
    if(!window.init()){
        spdlog::critical("Window Creation Failed - Canceling Application Creation");
        return  false;
    }

    spdlog::info("Starting UI Initialization");
    ui.init(window.getWindowPtr().get());

    return true;
}

void Application::run() {
    //Since this scope requires the window ptr, increase reference count
    std::shared_ptr<GLFWwindow> glfwWindowPtr = window.getWindowPtr();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool firstRun = true;

    while(!glfwWindowShouldClose(glfwWindowPtr.get())){
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput();

        ui.startUIFrame();

        ui.drawUi(window.getScreenSize());

        ui.endUIFrame();

        glfwPollEvents();
        glfwSwapBuffers(glfwWindowPtr.get());
    }

    ui.cleanUp();
}

void Application::processInput() {
    if (glfwGetKey(window.getWindowPtr().get(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window.getWindowPtr().get(), true);
    }
}
