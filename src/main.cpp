#include <iostream>
#include "core/application.h"
#include <memory>
#include <cstdlib>


//TODO: Set up logging

int main() {
    //set random number seed - maybe do this in main
    srand((unsigned) time(nullptr));

    //construct a new downlaoder manager application
    std::unique_ptr<Application> app = std::make_unique<Application>();
    //initialize the application and make it ready to run
    bool isAppReadyToRun = app->Init();

    if(isAppReadyToRun){
        app->Run();
    }

    return 0;
}
