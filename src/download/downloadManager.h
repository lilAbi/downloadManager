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
    ~DownloadManager() = default;

    void addTask(DownloadTask&& task);
    std::vector<DownloadTask> getDownloadList();
    DownloadTask generateDownloadTaskFromUrl(std::string link);
    void shutdown();

private:
    ThreadSafeQueue<DownloadTask> downloadQueue{};
    ThreadSafeVector<DownloadTask> downloadList{};
    ThreadPool threadPool{downloadQueue, downloadList};
};


#endif //DOWNLOADMANAGER_DOWNLOADMANAGER_H
