#ifndef DOWNLOADMANAGER_WORKERTHREAD_H
#define DOWNLOADMANAGER_WORKERTHREAD_H

#include "threadSafeQueue.h"
#include "task.h"

class WorkerThread {
public:

    explicit WorkerThread(int id, ThreadSafeQueue<Task>* queue) : threadID{id}, taskQueue{queue} {}

    void operator () ();

private:
    int threadID;
    ThreadSafeQueue<Task>* taskQueue;

};


#endif //DOWNLOADMANAGER_WORKERTHREAD_H
