#include "application.h"


Application::Application() {

}

Application::~Application() {
    CleanUp();  //application clean up
}

bool Application::Init() {
    //Initializes and creates the window object
    if(!window.CreateWindow()){
        static_assert(true, "Window creation failed");
        return false;
    }

    //initializes imgui
    if(!ui.InitGUI(window)){
        static_assert(true, "imgui failed to start");
        return false;
    }

    //downloading logic


    return true;
}

void Application::Run() {

    while(!glfwWindowShouldClose(window.GetWindowPtr().get())){
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ui.Start();
        ui.DrawUI();
        ui.End();
        glfwSwapBuffers(window.GetWindowPtr().get());
    }

    //shut down downloader thread

}

void Application::CleanUp() {
    window.DestroyWindow();
    ui.CleanUp();
}
