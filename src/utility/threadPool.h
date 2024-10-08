#ifndef DOWNLOADMANAGER_THREADPOOL_H
#define DOWNLOADMANAGER_THREADPOOL_H

#include "joinThreads.h"
#include "download/downloadWorker.h"
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(ThreadSafeQueue<DownloadTask>& tq);
    ~ThreadPool();

private:
    std::vector<std::thread> threads{};
    JoinThreads joinThreads{threads};
    std::atomic_bool done{false};

};


#endif //DOWNLOADMANAGER_THREADPOOL_H
