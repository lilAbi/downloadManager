#ifndef DOWNLOADMANAGER_DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_DOWNLOADMANAGER_H

#include "utility/threadSafeQueue.h"
#include "downloadTask.h"
#include "utility/threadPool.h"

//orchestrates the downloading system.
class DownloadManager {
public:
    DownloadManager(){
        auto* ptr = &downloadQueue;
        spdlog::info("task queue ptr {}", fmt::ptr(ptr));
    };
    ~DownloadManager() = default;
private:
    ThreadSafeQueue<DownloadTask> downloadQueue{};
    ThreadPool threadPool{downloadQueue};
    //TaskSchedular DownloadQueue;
    //ThreadSafe Downloadabel queue;

};


#endif //DOWNLOADMANAGER_DOWNLOADMANAGER_H
