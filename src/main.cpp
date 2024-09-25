#include "core/application.h"

int main() {

    Application downloadManager;

    if(downloadManager.init()){
        downloadManager.run();
    }

    return 0;
}
