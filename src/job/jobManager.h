#ifndef DOWNLOADMANAGER_JOBMANAGER_H
#define DOWNLOADMANAGER_JOBMANAGER_H


#include <vector>
#include <thread>
#include "threadSafeQueue.h"
#include "task.h"

//sub systems have a reference to this object and can submit jobs
class JobManager {
public:
    JobManager() = default;

    //bool SubmitTask();

    bool Init();

private:


private:
    std::vector<std::thread>            threadPool;
    std::vector<ThreadSafeQueue<Task>>  taskQueue;

};


#endif //DOWNLOADMANAGER_JOBMANAGER_H
