#ifndef DOWNLOADMANAGER_THREADSAFEVECTOR_H
#define DOWNLOADMANAGER_THREADSAFEVECTOR_H

#include <vector>
#include <condition_variable>
#include <mutex>
#include <memory>

#include "download/downloadTask.h"

template<typename T>
class ThreadSafeVector{
public:
    ThreadSafeVector() = default;
    ~ThreadSafeVector() = default;

    //push item and get index
    int pushItem(T& value);

    //update item at index
    bool updateItem(T& value, int index);

    //get item at index
    T& getItem(int index);

    //get a copy of the under lying pointer
    std::vector<T> getDataVector();

private:
    mutable std::mutex mutex;
    std::condition_variable conditionVariable;
    std::vector<T> data{};

};

template<typename T>
int ThreadSafeVector<T>::pushItem(T &value) {
    std::lock_guard<std::mutex> lock(mutex);
    data.push_back(value);
    return data.size();
}

template<typename T>
bool ThreadSafeVector<T>::updateItem(T &value, int index) {
    std::lock_guard<std::mutex> lock(mutex);
    if(data.size() > index){
        return false;
    }
    data[index] = value;
    return true;
}

template<typename T>
T& ThreadSafeVector<T>::getItem(int index) {
    std::lock_guard<std::mutex> lock(mutex);
    if(data.size() > index){
        return T{};
    }
    return data[index];
}

template<typename T>
std::vector<T> ThreadSafeVector<T>::getDataVector() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<T> dataCopy = data;
    return dataCopy;
}


#endif //DOWNLOADMANAGER_THREADSAFEVECTOR_H
