#include "application.h"

bool Application::init() {
    spdlog::info("Starting Application Initialization");

    if(!window.init()){
        spdlog::info("Window Creation Failed - Canceling Application Creation");
        return  false;
    }

    return true;
}

void Application::run() {
    //Since this scope requires the window ptr, increase reference count
    std::shared_ptr<GLFWwindow> glfwWindowPtr = window.getWindowPtr();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool firstRun = true;

    while(!glfwWindowShouldClose(glfwWindowPtr.get())){
        glfwPollEvents();
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(glfwWindowPtr.get());
    }
}
