

#include "threadPool.h"

ThreadPool::ThreadPool(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& vector) {

    //calculate amount of threads that is possible
    int threadCount = 4;

    for(int i = 0; i < threadCount; i++){
        threads.emplace_back(DownloadWorker(queue, vector, done));
    }
}

ThreadPool::~ThreadPool() {
}
