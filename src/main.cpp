
#include <core/application.h>
#include <memory>

int main() {

    //create a unique ptr to an Application obj; we will be referring to this obj as the main app obj
    std::unique_ptr<core::Application> application = std::make_unique<core::Application>();

    //Initialize sub-systems; if they pass then we can run the main app loop
    if(application->Init()){

    }

    return 0;
}
