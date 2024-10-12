#ifndef DOWNLOADMANAGER_APPLICATION_H
#define DOWNLOADMANAGER_APPLICATION_H

#include "spdlog/spdlog.h"
#include "window/appWindow.h"
#include "ui/ui.h"
#include "download/downloadManager.h"

class Application {
public:
    Application() = default;
    ~Application() {spdlog::critical("Destroying Application Class");}
    //initialize download manager subsystems
    bool init();
    //run application loop
    void run();
private:
    void processInput();
private:
    AppWindow window;
    Ui ui;
    DownloadManager downloadManager;
};


#endif //DOWNLOADMANAGER_APPLICATION_H
