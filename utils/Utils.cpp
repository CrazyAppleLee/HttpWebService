
#include "Utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>


using namespace WebServer;
using namespace std;

bool WebServer::setFdNonBlock(int fd)
{
    int flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1)
        return false;

    flag |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flag) == -1)
        return false;
    return true;
}
string WebServer::trimleft(const string &target, string sep)
{
    set<char> seChar;
    for(int i=0; i < sep.size(); i++){
        seChar.insert(sep[i]);
    }
    int i = 0;
    while(i < target.size() && seChar.find(target[i]) != seChar.end()){
        i++;
    }
    return target.substr(i, target.size() - i);
}

string WebServer::trimright(const string &target, string sep)
{
    set<char> seChar;
    for(int i=0; i < sep.size(); i++){
        seChar.insert(sep[i]);
    }
    int i = target.size() - 1;
    while(i >= 0 && seChar.find(target[i]) != seChar.end()){
        i--;
    }
    return target.substr(0, i + 1);
}   

string WebServer::trimLeftandRight(const std::string &target, std::string leftSep, std::string rightSep)
{
    string sStr = trimleft(target, leftSep);
    return trimright(sStr, rightSep);
}

vector<string> WebServer::split(const string &target, string token)
{
    vector<string> vString;
    string::size_type pos = 0;
    string::size_type p = target.find(token,pos);
    while(p != string::npos){
        vString.emplace_back(target.substr(pos, p - pos));
        pos = p + token.size();
        p = target.find(token, pos);
    }
    vString.emplace_back(target.substr(pos, target.size() - pos));
    return vString;
}
vector<string> WebServer::split1st(const string &target, string token)
{
        vector<string> vString;
    string::size_type pos = 0;
    string::size_type p = target.find(token,pos);
    if(p != string::npos){
        vString.emplace_back(target.substr(pos, p - pos));
        pos = p + token.size();
        p = target.find(token,pos);
    }
    vString.emplace_back(target.substr(pos, target.size() - pos));
    return vString;
}


bool WebServer::readWebPage(string path, string &content){
    string rootPath = "web";
    const int BUFFSIZE = 1024;
    if(path == "/"){
        path = "/index.html";
    }
    path = rootPath + path;
    int fd = open(path.c_str(), O_RDONLY);
    if(fd == -1) return false;
    char buff[1024];

    while(true)
    {
        int readNum = read(fd, buff, BUFFSIZE);
        if(readNum == 0) break;
        content.append(buff, readNum);
    }
    return true;
}

bool WebServer::str2int(const std::string &str, int &num)
{
    try{
        num = stoi(str);
        //cout << "str2int " << num << " " << str << endl;
        return true;
    }
    catch(exception e)
    {
        //cout << "str2int error " << str << endl;
        return false;
    }
}
