#ifndef DOWNLOADMANAGER_DOWNLOADWORKER_H
#define DOWNLOADMANAGER_DOWNLOADWORKER_H

#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>
#include "spdlog/spdlog.h"
#include "utility/threadSafeQueue.h"
#include "utility/threadSafeVector.h"
#include "curl/curl.h"
#include "downloadTask.h"

static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userData);
static int xtraInfoCallback(void *userData, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

struct DownloadProgress{
    ThreadSafeVector<DownloadTask>* downloadList{nullptr};
    int index{};
};

class DownloadWorker {
public:
    DownloadWorker(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& downloadListVec, std::atomic_bool& globalDone);
    ~DownloadWorker() = default;

    void operator() ();
private:
    ThreadSafeQueue<DownloadTask>& globalTaskQueue;
    ThreadSafeVector<DownloadTask>& downloadVec;
    std::atomic_bool& done;
    inline static int workerNum{0}; //debug
};


#endif //DOWNLOADMANAGER_DOWNLOADWORKER_H
