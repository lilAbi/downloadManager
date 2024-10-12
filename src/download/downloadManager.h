#ifndef DOWNLOADMANAGER_DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_DOWNLOADMANAGER_H

#include "downloadTask.h"
#include "utility/threadSafeQueue.h"
#include "utility/threadPool.h"
#include "utility/threadSafeVector.h"

//orchestrates the downloading system.
//http://ipv4.download.thinkbroadband.com:8080/1GB.zip
class DownloadManager {
public:
    DownloadManager() = default;
    ~DownloadManager(){spdlog::critical("Shutting DownloadManager");};

    void addTask(DownloadTask&& task);

    std::vector<DownloadTask> getDownloadList();

    DownloadTask generateDownloadTaskFromUrl(std::string link);

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
