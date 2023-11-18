#ifndef DOWNLOADMANAGER_APPLICATION_H
#define DOWNLOADMANAGER_APPLICATION_H

#include <thread>

#include "window.h"
#include "ui/applicationGui.h"
#include "download/downloadQueue.h"
#include "download/downloadScheduler.h"


/*
 * Main body of the application
 * Should contain everything
 */

class Application {
public:
    Application();
    ~Application();

    static Application& GetAppInstance();
    bool Init();
    void Run();
    void CleanUp();

private:
    Window          window;
    ApplicationGUI  ui;
    std::thread     downloaderThread;
    DownloadQueue   downloadQueue;
};

extern Application* appInstance;

#endif //DOWNLOADMANAGER_APPLICATION_H
