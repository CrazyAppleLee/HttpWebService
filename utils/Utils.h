#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

namespace WebServer{

    bool setFdNonBlock(int fd); //设置描述符为非阻塞
    bool str2int(const std::string &str, int &num);
    std::string trimleft(const std::string &target, std::string sep);
    std::string trimright(const std::string &target, std::string sep);
    std::string trimLeftandRight(const std::string &target, std::string leftSep, std::string rightSep);
    std::vector<std::string> split(const std::string &target, std::string token);
    std::vector<std::string> split1st(const std::string &target, std::string token);
    bool readWebPage(std::string path, std::string &content);
}

#endif