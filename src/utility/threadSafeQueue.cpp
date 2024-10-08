#include "threadSafeQueue.h"

template<typename T>
void ThreadSafeQueue<T>::push(T value) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(std::move(value));
    conditionVariable.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::waitAndPop(T &value) {
    std::unique_lock<std::mutex> lock{mutex};
    //block thread until the queue is
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

