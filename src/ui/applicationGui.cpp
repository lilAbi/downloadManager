#include "applicationGui.h"

bool ApplicationGUI::InitGUI(Window& windowPtr) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

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

    //Window 1
    //contains a text bar to input text from the user
    //also a button to start the download
    ImGui::SetNextWindowPos(ImVec2(0,0));



    ImGui::ShowDemoWindow();

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
