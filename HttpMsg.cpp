#include "HttpMsg.h"
#include "./utils/Utils.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;
using namespace WebServer;

bool HttpReqMsg::parseHttpReq(string msg){
    vector<string> vString = split(msg, "\r\n");
    if(vString.size() < 2) return false;
    vector<string> vtmp = split(vString[0], " ");
    _method = vtmp[0];
    _url = vtmp[1];
    _version = vtmp[2];
    //int i=1;
    for(int i = 1; i < vString.size(); i++)
    {
        if(vString[i] == "") break;
        vtmp = split(vString[i], ":");
        if(vtmp.size() < 2) continue;
        _headers[vtmp[0]] = vtmp[1];
    }
    _content = vString[vString.size() - 1];
    return true;
}

string HttpRspqMsg::toStr()
{
    ostringstream ss;
    ss << _version << " " << _status << " " << _description <<"\r\n";
    map<string, string>::iterator it = _headers.begin();
    for(; it != _headers.end(); it ++)
    {
        ss << it->first << ":" << it->second << "\r\n";
    }
    ss << "\r\n";
    ss << _content;
    return ss.str();
}