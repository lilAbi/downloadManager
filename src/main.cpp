#include "core/application.h"
#include "curl/curl.h"

int main() {

    //initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    Application downloadManager;

    if(downloadManager.init()){
        downloadManager.run();
    }

    curl_global_cleanup();
    return 0;
}
