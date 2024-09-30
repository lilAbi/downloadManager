#ifndef DOWNLOADMANAGER_APPLICATION_H
#define DOWNLOADMANAGER_APPLICATION_H

#include <spdlog/spdlog.h>
#include "window/appWindow.h"
#include "ui/ui.h"

class Application {
public:
    Application() = default;
    //initialize download manager subsystems
    bool init();
    //run application loop
    void run();
private:
    void processInput();
private:
    AppWindow window;
    Ui ui;
};


#endif //DOWNLOADMANAGER_APPLICATION_H
