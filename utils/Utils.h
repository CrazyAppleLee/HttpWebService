#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

namespace WebServer{

    bool setFdNonBlock(int fd); //设置描述符为非阻塞
    std::string trimleft(std::string target, std::string sep);
    std::vector<std::string> split(std::string target, std::string token);
    bool readWebPage(std::string path, std::string &content);
}

#endif