#ifndef DOWNLOADMANAGER_APPLICATIONGUI_H
#define DOWNLOADMANAGER_APPLICATIONGUI_H


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "core/window.h"


//make these static functions?
//static functions to draw "ui elements"


static void ShowDownloadUI(bool* shouldWindowBeOpen);
static void ShowAboutUI();
static void ShowLicenseUI();

class ApplicationGUI {
public:
    bool InitGUI(Window& windowPtr);

    void Start();
    void DrawUI();
    void End();

    void CleanUp();

private:
    Window* localWindowPtr;

};


#endif //DOWNLOADMANAGER_APPLICATIONGUI_H
