#ifndef DOWNLOADMANAGER_DOWNLOADTASK_H
#define DOWNLOADMANAGER_DOWNLOADTASK_H

#include <string>

enum class DownloadStatus {
    PENDING,
    DOWNLOADING,
    PAUSED,
    FINISHED,
    FAILED,
    ERROR
};

struct DownloadTask{
    std::string url;
    std::string outputPath;
    float progress;
    DownloadStatus status{DownloadStatus::ERROR};
};


#endif //DOWNLOADMANAGER_DOWNLOADTASK_H
