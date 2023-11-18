#ifndef DOWNLOADMANAGER_DOWNLOADSCHEDULER_H
#define DOWNLOADMANAGER_DOWNLOADSCHEDULER_H

#include <string>
#include <iostream>

#include "downloadQueue.h"

//this class is designed to run on a separate thread
//pool a downloadQueue object and based on
class DownloadScheduler {
public:

    explicit DownloadScheduler(DownloadQueue& dq) : downloadQueue{dq} {}

    void operator()();

private:
    DownloadQueue& downloadQueue;
};


#endif //DOWNLOADMANAGER_DOWNLOADSCHEDULER_H
