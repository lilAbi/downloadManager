#ifndef DOWNLOADMANAGER_THREADSAFEQUEUE_H
#define DOWNLOADMANAGER_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include "spdlog/spdlog.h"

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

template<typename T>
void ThreadSafeQueue<T>::push(T value) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(std::move(value));
    conditionVariable.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::waitAndPop(T &value) {
    std::unique_lock<std::mutex> lock{mutex};
    conditionVariable.wait(lock, [this]{return !queue.empty();});
    value = std::move(queue.front());
    queue.pop();
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop() {
    std::unique_lock<std::mutex> lock{mutex};
    conditionVariable.wait(lock, [this]{return !queue.empty();});
    std::shared_ptr<T> result(std::make_shared<T>(std::move(queue.front())));
    queue.pop();
    return result;
}

template<typename T>
bool ThreadSafeQueue<T>::tryPop(T &value) {
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.empty())
        return false;
    value = std::move(queue.front());
    queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::tryPop() {
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.empty())
        return std::shared_ptr<T>();
    std::shared_ptr<T> result(std::make_shared<T>(std::move(queue.front())));
    queue.pop();
    return result;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}

#endif //DOWNLOADMANAGER_THREADSAFEQUEUE_H
