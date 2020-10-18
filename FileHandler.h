#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include "FileData.h"
namespace WebServer{
    class FileHandler{
    private:
        
    public:
        static bool doRequset(const FileReqMsgST &stFileReqMsg, FileRspMsgST &stFileRspMsg);
        static bool getFileList(const std::string &path, FileInfoListST &vFileInfos);

    };
}
#endif 