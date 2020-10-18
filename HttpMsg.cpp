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
    _sMethod = vtmp[0];
    _sUrl = vtmp[1];
    _sVersion = vtmp[2];
    //int i=1;
    for(int i = 1; i < vString.size(); i++)
    {
        if(vString[i] == "") break;
        vtmp = split(vString[i], ":");
        if(vtmp.size() < 2) continue;
        _mHeaders[vtmp[0]] = vtmp[1];
    }
    _sContent = vString[vString.size() - 1];
    return true;
}

bool HttpReqMsg::parseRequsetLine(string msg, bool &bError)
{
    bError = false; 
    int p = msg.find("\r\n");
    if(p != string::npos)
    {
        string sLine = msg.substr(0,p); 
        vector<string> vTmp = split(sLine, " ");
        if(vTmp.size() < 3) 
        {
            bError = true;
            return false;
        }
        _sMethod = vTmp[0];
        _sUrl = vTmp[1];
        _sVersion = vTmp[2];
        return true;
    }
    return false;
}

bool HttpReqMsg::parseHeanders(std::string msg,bool &bError)
{
    bError = false;
    int p = msg.find("\r\n\r\n");
    if(p != string::npos)
    {
        vector<string> vLines = split(msg,"\r\n");
        if(vLines.size()<3) 
        {
            bError = true;
            return false;
        }
        for(int i = 1; i < vLines.size(); i++)
        {
            if(vLines[i] == "") break;
            vector<string> vTmp = split(vLines[i], ":");
            if(vTmp.size() < 2)
            {
                bError = true;
                return false;
            }
            _mHeaders[vTmp[0]] = vTmp[1]; 
        }
    }
    return false;
}
bool HttpReqMsg::parseContent(std::string msg,bool &bError)
{
    bError = false;
    vector<string> vTmp = split(msg, "\r\n\r\n");
    if(vTmp.size() < 2){
        bError = true;
        return false;
    }
    _sContent = vTmp[1];
    return true;
}
string HttpReqMsg::toStr()
{
    ostringstream ss;
    ss << _sMethod << " " << _sUrl << " " << _sVersion <<"\r\n";
    map<string, string>::iterator it = _mHeaders.begin();
    for(; it != _mHeaders.end(); it ++)
    {
        ss << it->first << ":" << it->second << "\r\n";
    }
    ss << "\r\n";
    ss << _sContent;
    return ss.str();
}

string HttpRspMsg::toStr()
{
    ostringstream ss;
    ss << _sVersion << " " << _sStatus << " " << _sDescription <<"\r\n";
    map<string, string>::iterator it = _mHeaders.begin();
    for(; it != _mHeaders.end(); it ++)
    {
        ss << it->first << ":" << it->second << "\r\n";
    }
    ss << "\r\n";
    ss << _sContent;
    return ss.str();
}