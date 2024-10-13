#include "downloadManager.h"

void DownloadManager::addTask(DownloadTask&& task) {
    downloadQueue.push(task);
}

std::vector<DownloadTask> DownloadManager::getDownloadList() {
    return downloadList.getDataVector();
}

DownloadTask DownloadManager::generateDownloadTaskFromUrl(std::string link) {
    DownloadTask task;

    auto position = link.find_last_of('/');

    if(position == std::string::npos){
        return DownloadTask{.name = link, .url = link};
    }

    task.url = link;
    task.name = link.substr(position + 1, link.size());

    return task;
}

void DownloadManager::shutdown(){
    threadPool.done = true;
    downloadQueue.terminate();
};
