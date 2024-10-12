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

void Ui::drawUi(std::pair<int,int> screenSize, DownloadManager& dm) {
    //background window pane ------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, screenSize.second));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5f, 0.0f, 0.0f, 1.0f));
    ImGuiWindowFlags background = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration;
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
        ImGui::OpenPopup("Add-Download");
    }

    //create popup for download in center
    auto center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    static std::string downloadURL{};
    if(ImGui::BeginPopupModal("Add-Download", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration)){
        ImGui::SetNextItemWidth(360.0f);
        ImGui::InputText("", &downloadURL);

        if(ImGui::Button("Add", ImVec2(120,0))){
            dm.addTask(DownloadTask{.url = downloadURL});
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 112.0f, 0.0f);

        if(ImGui::Button("Close", ImVec2(120,0))){ImGui::CloseCurrentPopup();}

        ImGui::EndPopup();
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

    //based of a "metadata list" that object gets iterated through
    ImGui::SetNextWindowPos(ImVec2(0.0f + 15.0f, 125.0f + 15.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first - 30.0f, screenSize.second - 125.0f - 20.0f - 30.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.8f, 0.4f, 0.9f, 1.0f));
    ImGuiWindowFlags downloadListContentWindow = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs;
    ImGui::Begin("downloadListContentWindow", nullptr, downloadListContentWindow);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.3f, 0.4f, 1.0f));
    ImGui::BeginChild("Toolbar", ImVec2(0, 30.0f), 0, 0);
    ImGui::EndChild();
    ImGui::BeginChild("ScrollArea", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    //static std::vector<std::pair<std::string,float>> downloads = {{"File1.zip", 0.5f}, {"File2.zip", 0.75f}};
    std::vector<DownloadTask> downloadListCopy = std::move(dm.getDownloadList());
    for(auto& download : downloadListCopy){

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.9f, 0.3f, 0.1f, 1.0f));
        std::string childLabel = download.url + "-child";
        ImGui::BeginChild(childLabel.c_str(), ImVec2(0, 80.0f), 0, 0);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30.0f);

        bool checkbox = true;
        std::string checkboxLabel = download.url + "-checkbox";
        ImGui::Checkbox(childLabel.c_str(), &checkbox);

        ImGui::SameLine(0, 100.0f);

        ImGui::SetNextItemWidth(200.0f);
        std::string inputTextLabel = download.outputPath + "-textbox";
        ImGui::InputText(inputTextLabel.c_str(), &download.outputPath);

        ImGui::SameLine(0, 100.0f);
        ImGui::ProgressBar(-1.0f * (float)ImGui::GetTime(), ImVec2(-FLT_MIN, 0),  "Downloading..");

        ImGui::EndChild();

    }

    ImGui::EndChild();

    ImGui::End();

    ImGui::End(); //end of download list window pane ---------------------------------------------------------------------



    //bottom tool bar list window pane ------------------------------------------------------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(0.0f, screenSize.second - 20.0f));
    ImGui::SetNextWindowSize(ImVec2(screenSize.first, 20.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.5f, 0.9f, 1.0f));
    ImGuiWindowFlags bottomToolbar = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration;
    ImGui::Begin("bottomToolbar", nullptr, bottomToolbar);

    static std::string speedText{"2.248 mb/s"};
    ImGui::SetCursorScreenPos(ImVec2(0.0f, screenSize.second - 20.0f));
    ImGui::SetNextItemWidth(75.0f);
    ImGui::InputText("", &speedText);

    ImGui::SetCursorScreenPos(ImVec2(screenSize.first - 70.0f, screenSize.second - 20.0f));
    if(ImGui::Button("Settings", ImVec2(70, 20))){

    }

    ImGui::End(); //end of bottom toolbar window pane ---------------------------------------------------------------------


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
