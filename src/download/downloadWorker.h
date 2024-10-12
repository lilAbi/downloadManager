#ifndef DOWNLOADMANAGER_DOWNLOADWORKER_H
#define DOWNLOADMANAGER_DOWNLOADWORKER_H

#include <atomic>
#include <thread>
#include <chrono>
#include "spdlog/spdlog.h"
#include "utility/threadSafeQueue.h"
#include "utility/threadSafeVector.h"
#include "curl/curl.h"
#include "downloadTask.h"

class DownloadWorker {
public:
    DownloadWorker(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& downloadListVec, std::atomic_bool& globalDone);
    ~DownloadWorker(){
        spdlog::critical("shutting down worker thread {}", workerNum);
    };

    void operator() ();
private:
    ThreadSafeQueue<DownloadTask>& globalTaskQueue;
    ThreadSafeVector<DownloadTask>& downloadVec;
    std::atomic_bool& done;
    inline static int workerNum{0}; //debug
};


#endif //DOWNLOADMANAGER_DOWNLOADWORKER_H
