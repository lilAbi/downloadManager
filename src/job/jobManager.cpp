#include "jobManager.h"

bool JobManager::Init() {
    //create maxThreads-1 worker threads and assign them an ID and their respective worker function

    int numOfThreads = static_cast<int>(std::thread::hardware_concurrency()) - 1;

    //reserve space to make new threads;
    threadPool.reserve(numOfThreads);
    taskQueue = std::move(std::vector<ThreadSafeQueue<Task>>{static_cast<size_t>(numOfThreads)});

    //construct threads
    for(int n = 0; n <= numOfThreads; n++){
        threadPool.emplace_back(n, taskQueue[n]);
    }


    return true;
}
