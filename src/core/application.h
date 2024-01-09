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

//downloading application that shows extra information

class Application {
public:
    Application();
    ~Application();

    bool Init();
    void Run();
    void CleanUp();

private:
    Window          window;
    ApplicationGUI  ui;
};


#endif //DOWNLOADMANAGER_APPLICATION_H
