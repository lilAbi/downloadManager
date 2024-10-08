#ifndef DOWNLOADMANAGER_THREADSAFEQUEUE_H
#define DOWNLOADMANAGER_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() =  default;

    void push(T value);

    void waitAndPop(T& value);
    std::shared_ptr<T> waitAndPop();

    bool tryPop(T& value);
    std::shared_ptr<T> tryPop();

    bool empty();

private:
    mutable std::mutex mutex;
    std::condition_variable conditionVariable;
    std::queue<T> queue;
};


#endif //DOWNLOADMANAGER_THREADSAFEQUEUE_H
