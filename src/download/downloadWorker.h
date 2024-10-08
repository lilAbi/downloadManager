#ifndef DOWNLOADMANAGER_DOWNLOADWORKER_H
#define DOWNLOADMANAGER_DOWNLOADWORKER_H

#include <atomic>
#include <thread>
#include <chrono>
#include "spdlog/spdlog.h"
#include "utility/threadSafeQueue.h"
#include "downloadTask.h"

class DownloadWorker {
public:
    DownloadWorker(ThreadSafeQueue<DownloadTask>& tq, std::atomic_bool& globalDone);
    ~DownloadWorker() = default;

    void operator() ();
private:
    ThreadSafeQueue<DownloadTask>& globalTaskQueue;
    std::atomic_bool& done;
    inline static int workerNum{0};
};


#endif //DOWNLOADMANAGER_DOWNLOADWORKER_H
