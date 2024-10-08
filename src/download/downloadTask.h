#ifndef DOWNLOADMANAGER_DOWNLOADTASK_H
#define DOWNLOADMANAGER_DOWNLOADTASK_H

#include <string>

enum class DownloadStatus {
    PENDING,
    DOWNLOADING,
    PAUSED,
    FINISHED,
    FAILED
};

struct DownloadTask{
    std::string url;
    std::string outputPath;
    float progress;
    DownloadStatus status{DownloadStatus::FAILED};
};


#endif //DOWNLOADMANAGER_DOWNLOADTASK_H
