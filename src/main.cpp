#include <iostream>
#include "core/application.h"
#include <memory>
#include <cstdlib>


//TODO: Set up logging

int main() {
    //set random number seed - maybe do this in main
    srand((unsigned) time(nullptr));

    //construct a new downlaoder manager application
    std::unique_ptr<Application> downloadManagerApp = std::make_unique<Application>();
    //initialize the application and make it ready to run
    bool isAppReadyToRun = downloadManagerApp->Init();

    if(isAppReadyToRun){
        downloadManagerApp->Run();
    }

    return 0;
}
