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
        std::map<std::string, std::string> header;
        std::string content;
    };


    bool setFdNonBlock(int fd); //设置描述符为非阻塞
    std::string trimleft(std::string target, std::string sep);
    std::vector<std::string> split(std::string target, std::string token);
}

#endif