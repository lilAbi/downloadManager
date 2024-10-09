#include "downloadWorker.h"

DownloadWorker::DownloadWorker(ThreadSafeQueue<DownloadTask> &tq, std::atomic_bool& globalDone): done{globalDone}, globalTaskQueue{tq}{}


void DownloadWorker::operator()() {
    int localWorkerId = workerNum++;
    spdlog::info("Starting worker thread {}", localWorkerId);
    //setup libcurl library

    while(!done){
        spdlog::info("Grabbing task from work queue on worker thread {}", localWorkerId);

        //local variable to hold task
        DownloadTask task;

        //wait for a task to be free
        globalTaskQueue.waitAndPop(task, done);
        if(done) break; //if application is done quit

        if(task.status == DownloadStatus::ERROR){
            spdlog::info("task failed on worker thread {}", localWorkerId);
        }
    }

}
