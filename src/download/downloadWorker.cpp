#include "downloadWorker.h"

DownloadWorker::DownloadWorker(ThreadSafeQueue<DownloadTask> &tq, std::atomic_bool& globalDone): done{globalDone}, globalTaskQueue{tq}{}

void DownloadWorker::operator()() {
    spdlog::info("Starting worker thread");

    while(!done){
        //try to pop downloaditem from task
        spdlog::info("work loop start");
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

}
