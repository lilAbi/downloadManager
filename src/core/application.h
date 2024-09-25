

#ifndef DOWNLOADMANAGER_APPLICATION_H
#define DOWNLOADMANAGER_APPLICATION_H

#include <spdlog/spdlog.h>

#include "window/appWindow.h"

class Application {
public:
    Application() = default;
    //initialize download manager subsystems
    bool init();
    //run application loop
    void run();
private:
    AppWindow window;
};


#endif //DOWNLOADMANAGER_APPLICATION_H
