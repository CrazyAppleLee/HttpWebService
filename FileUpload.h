#ifndef FILEUPLOAD_H
#define FILEUPLOAD_H

#include "C_SQueue.h"
#include <string>
#include <vector>

namespace WebServer{
    struct FileMsg
    {
        std::string userid;     //用户id
        std::string savePath;   //保存路径
        std::string fileName;   //文件名
        std::string MD5;
        std::msgType;           //消息类型
        std::int totalNum;      //分片数量
        std::int seq;           //序列号
        std::content;           //内容
    };
    
    class FileUpLoad{
    private:

    public:
        static std::vector<std::sting> getFileList(FileMsg fileMsg); //path下的文件列表
        static int getCheckPoint(FileMsg fileMsg);    //
        static void SaveFile(FileMsg fileMsg);  //
    };
}
#endif