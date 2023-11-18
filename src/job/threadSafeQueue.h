#ifndef DOWNLOADMANAGER_THREADSAFEQUEUE_H
#define DOWNLOADMANAGER_THREADSAFEQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void Push(T element);
    bool empty();
    void WaitAndPop(T& element);
    std::shared_ptr<T> WaitAndPop();
    bool TryPop(T& element);
    std::shared_ptr<T> TryPop();

    ThreadSafeQueue(ThreadSafeQueue&&) noexcept {};
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) noexcept {return *this;};

private:
    mutable std::mutex mutex{};
    std::queue<T> queue{};
    std::condition_variable conditionVariable{};

};

template<typename T>
void ThreadSafeQueue<T>::Push(T element) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    queue.push(std::move(element));
    conditionVariable.notify_one();
}

template<typename T>
bool ThreadSafeQueue<T>::empty() {
    std::lock_guard<std::mutex> lockGuard(mutex);
    return queue.empty();
}

template<typename T>
void ThreadSafeQueue<T>::WaitAndPop(T &element) {
    std::unique_lock<std::mutex> uniqueLock(mutex);
    conditionVariable.wait(uniqueLock, [this]{return !queue.empty();});
    element = std::move(queue.front());
    queue.pop();
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::WaitAndPop() {
    std::unique_lock<std::mutex> uniqueLock(mutex);
    conditionVariable.wait(uniqueLock, [this]{return !queue.empty();});
    std::shared_ptr<T> element( std::make_shared<T>(std::move(queue.front())) );
    queue.pop();
    return element;
}

template<typename T>
bool ThreadSafeQueue<T>::TryPop(T &element) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    if( queue.empty() ) {return false;}
    element = std::move(queue.front());
    queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::TryPop() {
    std::lock_guard<std::mutex> lockGuard(mutex);
    if( queue.empty() ) {return std::shared_ptr<T>();}
    std::shared_ptr<T> element( std::make_shared<T>(std::move(queue.front())) );
    queue.pop();
    return element;
}

#endif //DOWNLOADMANAGER_THREADSAFEQUEUE_H
