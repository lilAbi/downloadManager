#include "downloadWorker.h"

DownloadWorker::DownloadWorker(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& vec, std::atomic_bool& globalDone)
: globalTaskQueue{queue}, downloadVec{vec}, done{globalDone}{}


void DownloadWorker::operator()() {
    int localWorkerId = workerNum++;
    spdlog::info("Starting worker thread {}", localWorkerId);

    while(!done){
        //local variable to hold task
        DownloadTask task;

        //wait for a task to be free
        globalTaskQueue.waitAndPop(task, done);
        if(done) break; //if application is done quit

        //add task to outbound vector
        int index = downloadVec.pushItem(task);

        //initialize easy curl handle
        void* curlHandle = curl_easy_init();
        if(curlHandle){
            curl_easy_setopt(curlHandle, CURLOPT_URL, task.url.c_str());
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curlHandle, CURLOPT_XFERINFOFUNCTION, xtraInfoCallback);
            curl_easy_setopt(curlHandle, CURLOPT_NOPROGRESS, 0); //enable progress

            FILE* downloadFile = fopen(task.name.c_str(), "wb");
            if(downloadFile){
                DownloadProgress downloadProgress {&downloadVec, index};
                curl_easy_setopt(curlHandle, CURLOPT_XFERINFODATA, &downloadProgress);
                curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, downloadFile); //links to the "userdata" argument
                spdlog::info("Downloading");
                curl_easy_perform(curlHandle); //performs download
            }

            fclose(downloadFile); //close file
        } else {
            spdlog::critical("curl handle error");
        }

        curl_easy_cleanup(curlHandle);
    }

}

static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userData){
    size_t written = fwrite(ptr, size, nmemb, (FILE*)userData);
    return written;
}

static int xtraInfoCallback(void* userData, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow){
    if (dltotal > 0) {
        float newProgress = (float)dlnow/(float)dltotal;
        auto* taskProgress = static_cast<DownloadProgress*>(userData);
        auto* downloadItem = taskProgress->downloadList->getItem(taskProgress->index);
        downloadItem->progress = newProgress;
    }
    return 0;
}
