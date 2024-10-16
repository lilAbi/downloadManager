#ifndef DOWNLOADMANAGER_THREADPOOL_H
#define DOWNLOADMANAGER_THREADPOOL_H

#include "joinThreads.h"
#include "download/downloadWorker.h"
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& vector);
    ~ThreadPool();

public:
    std::atomic_bool done{false};
private:
    std::vector<std::thread> threads{};
    JoinThreads joinThreads{threads};
};


#endif //DOWNLOADMANAGER_THREADPOOL_H
