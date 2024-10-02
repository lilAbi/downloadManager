#include "ui.h"

bool Ui::init(GLFWwindow* glfwWindowPtr) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwWindowPtr, true);
#ifdef __APPLE__
    ImGui_ImplOpenGL3_Init("#version 410");
#else
    ImGui_ImplOpenGL3_Init("#version 460");
#endif
    return true;
}

void Ui::startUIFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Ui::drawUi(std::pair<int,int> screenSize) {
    //spdlog::info("Window size is {} {}", screenSize.first, screenSize.second);
    //background window pane ------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, screenSize.second));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5f, 0.0f, 0.0f, 1.0f));
    ImGuiWindowFlags background = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs;
    ImGui::Begin("Background", nullptr, background);
    ImGui::End(); //end of background window pane --------------------------------------------------------------------

    //toolbar window pane --------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, 125.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    ImGuiWindowFlags topToolbar =  ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("topToolbar", nullptr, topToolbar);

    //"adding new download" button
    ImGui::SetCursorPos(ImVec2(37.5f, 37.5f));
    if(ImGui::Button("+", ImVec2(50, 50))){

    }

    //"resume selected downloads" button
    ImGui::SameLine(0.0f, 17.5f);
    if(ImGui::Button("|>", ImVec2(50, 50))){

    }

    //"pause selected downloads" button
    ImGui::SameLine(0.0f, 17.5f);
    if(ImGui::Button("| |", ImVec2(50, 50))){

    }

    //"delete selected downloads" button
    ImGui::SameLine(0.0f, 17.5f);
    if(ImGui::Button("Trash", ImVec2(50, 50))){

    }

    //search text box
    static std::string searchTextBoxString{"Search"};
    ImGui::SetCursorScreenPos(ImVec2(screenSize.first - 275.0f, 52.0f));
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("", &searchTextBoxString);

    ImGui::SetCursorScreenPos(ImVec2(screenSize.first - 60.0f, 37.5f));
    if(ImGui::Button("Search", ImVec2(50, 50))){

    }
    ImGui::End(); //end of toolbar window pane ---------------------------------------------------------------------------

    //download list window pane ------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f,125.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, screenSize.second - 125.0f - 20.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5f, 0.1f, 0.3f, 1.0f));
    ImGuiWindowFlags downloadList = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs;
    ImGui::Begin("downloadList", nullptr, downloadList);
    ImGui::End(); //end of download list window pane ---------------------------------------------------------------------

    //bottom tool bar list window pane ------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f, screenSize.second - 20.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, 20.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.5f, 0.9f, 1.0f));
    ImGuiWindowFlags bottomToolbar = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs;
    ImGui::Begin("bottomToolbar", nullptr, bottomToolbar);

    static std::string speedText{"2.248 mb/s"};
    ImGui::SetCursorScreenPos(ImVec2(0.0f, screenSize.second - 20.0f));
    ImGui::SetNextItemWidth(75.0f);
    ImGui::InputText("", &speedText);

    ImGui::End(); //end of download list window pane ---------------------------------------------------------------------




}

void Ui::endUIFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Ui::cleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Ui::drawBackground() {

}

void Ui::drawToolbar() {

}
