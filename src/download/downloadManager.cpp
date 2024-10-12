#include "downloadManager.h"

void DownloadManager::addTask(DownloadTask&& task) {
    downloadQueue.push(task);
}

std::vector<DownloadTask> DownloadManager::getDownloadList() {
    return std::move(downloadList.getDataVector());
}
