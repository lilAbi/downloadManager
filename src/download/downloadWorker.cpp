#include "downloadWorker.h"

DownloadWorker::DownloadWorker(ThreadSafeQueue<DownloadTask> &tq, std::atomic_bool& globalDone): done{globalDone}, globalTaskQueue{tq}{}


void DownloadWorker::operator()() {
    int localWorkerId = workerNum++;
    spdlog::info("Starting worker thread {}", localWorkerId);
    auto* queuePtr = &globalTaskQueue;
    spdlog::info("worker thread {} queue ptr {}", localWorkerId, fmt::ptr(queuePtr));
    //setup libcurl library

    while(!done){
        //try to pop downloaditem from task
        spdlog::info("work loop start on worker thread {}", localWorkerId);

        DownloadTask task;
        globalTaskQueue.waitAndPop(task, done);

        if(task.status == DownloadStatus::ERROR){
            spdlog::info("task failed on worker thread {}", localWorkerId);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

}
