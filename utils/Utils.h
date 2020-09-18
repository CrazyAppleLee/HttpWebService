#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

namespace WebServer{

    struct HttpReqMsg{
        std::string method;
        std::string url;
        std::string version;
        std::map<std::string, std::string> headers;
        std::string content;
        bool parseHttpReq(std::string msg);
    };

    struct HttpRspqMsg{
        std::string version = "HTTP/1.1";
        std::string status = "200";
        std::string description = "ok"; 
        std::map<std::string, std::string> headers;
        std::string content;
        std::string toStr();
    };

    bool setFdNonBlock(int fd); //设置描述符为非阻塞
    std::string trimleft(std::string target, std::string sep);
    std::vector<std::string> split(std::string target, std::string token);
    bool readWebPage(std::string path, std::string &content);
}

#endif