#ifndef DOWNLOADMANAGER_JOINTHREADS_H
#define DOWNLOADMANAGER_JOINTHREADS_H

#include <thread>

class JoinThreads{
public:
    explicit JoinThreads(std::vector<std::thread>& threadList): threads(threadList) {}
    ~JoinThreads() {
        for (auto& thread : threads){
            if(thread.joinable())
                thread.join();
        }
    }
private:
    std::vector<std::thread>& threads;
};


#endif //DOWNLOADMANAGER_JOINTHREADS_H
