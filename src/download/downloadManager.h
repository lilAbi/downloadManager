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
    ~DownloadManager(){spdlog::critical("Shutting DownloadManager");};

    void addTask(DownloadTask&& task);

    std::vector<DownloadTask> getDownloadList();

    void shutdown(){
        threadPool.done = true;
        downloadQueue.terminate();
    };

private:
    ThreadSafeQueue<DownloadTask> downloadQueue{};
    ThreadSafeVector<DownloadTask> downloadList{};
    ThreadPool threadPool{downloadQueue, downloadList};
    //TaskSchedular DownloadQueue;
    //ThreadSafe Downloadabel queue;

};


#endif //DOWNLOADMANAGER_DOWNLOADMANAGER_H
