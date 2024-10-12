#include "downloadWorker.h"

DownloadWorker::DownloadWorker(ThreadSafeQueue<DownloadTask>& queue, ThreadSafeVector<DownloadTask>& vec, std::atomic_bool& globalDone)
: globalTaskQueue{queue}, downloadVec{vec}, done{globalDone}{}


void DownloadWorker::operator()() {
    int localWorkerId = workerNum++;
    spdlog::info("Starting worker thread {}", localWorkerId);
    //setup libcurl library
    void* curlHandle = curl_easy_init();

    while(!done){
        spdlog::info("Grabbing task from work queue on worker thread {}", localWorkerId);

        //local variable to hold task
        DownloadTask task;

        //wait for a task to be free
        globalTaskQueue.waitAndPop(task, done);
        if(done) break; //if application is done quit

        /*
        if(curlHandle){

            //open a file


        } else {
            spdlog::critical("curl handle error");
            continue;
        }
         */
        int index = downloadVec.pushItem(task);


    }

}
