#include "jobManager.h"

bool JobManager::Init() {
    //create maxThreads-1 worker threads and assign them an ID and their respective worker function
    int numOfThreads = static_cast<int>(std::thread::hardware_concurrency()) - 1;

    //reserve space to make new threads;
    threadPool.reserve(numOfThreads);

    //construct threads
    for(int n = 0; n <= numOfThreads; n++){
        threadPool.emplace_back(WorkerThread(n, &taskQueue));
    }


    return true;
}

void JobManager::SubmitTask(Task task) {
    taskQueue.Push(task);
}
