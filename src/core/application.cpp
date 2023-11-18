#include "application.h"

Application* appInstance = nullptr;

Application::Application() {
    //set the global static appInstance ptr to last application object made (should only be 1)
    appInstance = this;
}

Application::~Application() {
    CleanUp();  //application clean up
    appInstance = nullptr; //set global app instance to null
}

Application &Application::GetAppInstance() {
    return *appInstance;
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


    //start the downloader schedular thread
    downloaderThread = std::move(std::thread(DownloadScheduler{downloadQueue}));


    return true;
}

void Application::Run() {

    while(!glfwWindowShouldClose(window.GetWindowPtr().get())){
        glfwPollEvents();
        ui.Start();

        ui.DrawUI();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ui.End();
        glfwSwapBuffers(window.GetWindowPtr().get());
    }

    //shut down downloader thread
    downloaderThread.join();

}

void Application::CleanUp() {
    window.DestroyWindow();
    ui.CleanUp();
}
