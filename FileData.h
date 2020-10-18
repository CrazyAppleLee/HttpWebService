#ifndef FILEDATA_H
#define FILEDATA_H
#include <string>
#include <vector>
namespace WebServer{
    enum FileMsgType
    {
        MSG_TYPE_LS = 0, //目录列表
        MSG_TYPE_SAVE, //文件保存
    };
    enum FileType
    {
        TYPE_FILE = 0, //文件
        TYPE_DIR //目录文件
    };

    typedef struct FileInfo
    {
        std::string sFileName;
        std::string sPath;
        FileType iFileType;
        int iSize;
        bool readFromJson(const std::string &sStr);
        std::string toJsonStr();
    } FileInfoST;

    typedef struct FileInfoList
    {
        std::vector<FileInfoST> vValue;
        void push_back(FileInfoST &value)
        {
            vValue.push_back(value);
        }
        int size()
        {
            return vValue.size();
        }
        FileInfoST& operator[](std::size_t i){
            return vValue[i];
        }
        bool readFromJson(const std::string &sStr);
        std::string toJsonStr();
    } FileInfoListST;
    //std::vector<FileInfo> FileInfoList;

    // typedef struct FileMsg_ 
    // {
    //     std::string sUserid;     //用户id
    //     std::string sSavePath;   //保存路径
    //     std::string sPath;
    //     std::string sFileName;   //文件名
    //     std::string sMd5;
    //     FileMsgType sMsgType;           //消息类型
    //     bool ret;           //返回值
    //     int iTotalNum;      //分块数量
    //     int iSeq;           //序列号（分块号）
    //     int iAck;           //确认号
    //     bool bAck;          //确认号有效
    //     std::string sContent;           //内容
    //     FileInfoList vFileList;
    // } FileMsg;

    typedef struct FileReqMsg
    {
        std::string sUserid;     //用户id
        std::string sPath;
        std::string sFileName;   //文件名
        std::string sMd5;
        FileMsgType sMsgType;           //消息类型
        int iTotalNum;      //分块数量
        int iSeq;           //序列号（分块号
        std::string sContent;           //内容
        int iSize; //内容字节数
    } FileReqMsgST;

    typedef struct FileRspMsg
    {
        std::string sUserid;     //用户id
        std::string sPath;
        std::string sFileName;   //文件名
        std::string sMd5;
        FileMsgType sMsgType;           //消息类型
        bool bRet;           //返回值
        int iAck;           //确认号
        int iSaveSize;      //已经接受大小
        //bool bAck;          //确认号有效
        std::string sContent;
    } FileRspMsgST;
}


#endif 