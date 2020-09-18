
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
string WebServer::trimleft(string target, string sep)
{
    set<char> sChar;
    for(int i=0; i < sep.size(); i++){
        sChar.insert(sep[i]);
    }
    int i = 0;
    while(i < target.size() && sChar.find(target[i]) != sChar.end()){
        i++;
    }
    return target.substr(i, target.size() - i);
}

vector<string> WebServer::split(string target, string token)
{
    vector<string> vString;
    string::size_type pos = 0;
    string::size_type p = target.find(token,pos);
    while(p != string::npos){
        vString.push_back(target.substr(pos, p - pos));
        pos = p + token.size();
        p = target.find(token,pos);
    }
    vString.push_back(target.substr(pos, target.size() - pos));
    return vString;
}

bool HttpReqMsg::parseHttpReq(std::string msg){
    vector<string> vString = split(msg, "\r\n");
    if(vString.size() < 2) return false;
    vector<string> vtmp = split(vString[0], " ");
    method = vtmp[0];
    url = vtmp[1];
    version = vtmp[2];
    //int i=1;
    for(int i = 1; i < vString.size(); i++)
    {
        if(vString[i] == "") break;
        vtmp = split(vString[i], ":");
        if(vtmp.size() < 2) continue;
        headers[vtmp[0]] = vtmp[1];
    }
    content = vString[vString.size() - 1];
    return true;
}

string HttpRspqMsg::toStr()
{
    ostringstream ss;
    ss << version << " " << status << " " <<description <<"\r\n";
    map<string, string>::iterator it = headers.begin();
    for(; it != headers.end(); it ++)
    {
        ss << it->first << ":" << it->second << "\r\n";
    }
    ss << "\r\n";
    ss << content;
    return ss.str();
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
