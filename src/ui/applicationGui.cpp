#include "applicationGui.h"

bool ApplicationGUI::InitGUI(Window& windowPtr) {

    localWindowPtr = &windowPtr;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    ImGui_ImplGlfw_InitForOpenGL(windowPtr.GetWindowPtr().get(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    return true;
}

void ApplicationGUI::Start() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void ApplicationGUI::DrawUI() {

    static bool showLicenseWindowFlag{false};
    static bool showAboutWindowFlag{false};
    static bool showDownloadWindowFlag{false};

    //Only 1 Window
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(localWindowPtr->windowWidth), static_cast<float>(localWindowPtr->windowHeight)));

    //set up window flags
    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= (ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar ) ;


    ImGui::Begin("Main Window", nullptr, windowFlags); //Main Window Start

    if(showDownloadWindowFlag) ShowDownloadUI(&showDownloadWindowFlag);
    if(showAboutWindowFlag) ShowAboutUI();
    if(showLicenseWindowFlag) ShowLicenseUI();

    //draw menu bar
    if(ImGui::BeginMenuBar()){
        //about menu that explains how to use the application

        if(ImGui::BeginMenu("Menu")){
            ImGui::MenuItem("New Download");    //open a window and start off a new downlaod
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")){
            ImGui::MenuItem("About");   //general about information of the project
            ImGui::MenuItem("License"); //general license information
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

    ImGui::End(); //Main Window End

}

void ApplicationGUI::End() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ApplicationGUI::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void ShowDownloadUI(bool* shouldWindowBeOpen){
}

static void ShowAboutUI(){

}

static void ShowLicenseUI(){

}