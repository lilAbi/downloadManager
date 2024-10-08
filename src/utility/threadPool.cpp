

#include "threadPool.h"

ThreadPool::ThreadPool(ThreadSafeQueue<DownloadTask>& tq) {

    //calculate amount of threads that is possible
    int threadCount = 4;

    for(int i = 0; i < threadCount; i++){
        threads.emplace_back(DownloadWorker(tq,done));
    }
}

ThreadPool::~ThreadPool() {
    done = true;
}
