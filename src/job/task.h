#ifndef DOWNLOADMANAGER_TASK_H
#define DOWNLOADMANAGER_TASK_H

struct Task;

using JobFunction = void (*) (Task*, const void*);

class Task{
    JobFunction function;
};


#endif //DOWNLOADMANAGER_TASK_H
