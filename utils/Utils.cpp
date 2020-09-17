
#include "Utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <set>


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

