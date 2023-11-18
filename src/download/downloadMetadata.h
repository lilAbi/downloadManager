#ifndef DOWNLOADMANAGER_DOWNLOADMETADATA_H
#define DOWNLOADMANAGER_DOWNLOADMETADATA_H

#include <string>

enum class DownloadState{
    READY,              //The current item ready to download
    DOWNLOADING,        //The current item is currently being downloaded
    STOPPED,            //The current item has stopped its downloading
    ERROR               //The current item has ran into an error
};

struct DownloadMetadata{
    std::string url;                    //location of the uri
    DownloadState state;
};




#endif //DOWNLOADMANAGER_DOWNLOADMETADATA_H
