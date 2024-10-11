#ifndef DOWNLOADMANAGER_DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_DOWNLOADMANAGER_H

#include "downloadTask.h"
#include "utility/threadSafeQueue.h"
#include "utility/threadPool.h"
#include "utility/threadSafeVector.h"

//orchestrates the downloading system.
class DownloadManager {
public:
    DownloadManager() = default;
    ~DownloadManager() = default;

    void shutdown(){
        downloadQueue.terminate();
    };

private:
    ThreadSafeQueue<DownloadTask> downloadQueue{};
    ThreadSafeVector<DownloadTask> downloadList{};
    ThreadPool threadPool{downloadQueue};
    //TaskSchedular DownloadQueue;
    //ThreadSafe Downloadabel queue;

};


#endif //DOWNLOADMANAGER_DOWNLOADMANAGER_H
