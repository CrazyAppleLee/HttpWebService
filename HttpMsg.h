#ifndef HTTPMSG_H
#define HTTPMSG_H

#include <string>
#include <map>
namespace WebServer{
    class HttpReqMsg{
    public:
        HttpReqMsg(){}
        std::string _sMethod;
        std::string _sUrl;
        std::string _sVersion;
        std::map<std::string, std::string> _mHeaders; //头属性
        std::string _sContent;
        //std::map<std::string,std::string> _mQuery;
        bool parseHttpReq(std::string msg);
        bool parseRequsetLine(std::string msg,bool &bError);
        bool parseHeanders(std::string msg,bool &bError);
        bool parseContent(std::string msg,bool &bError);
        //bool parseURL();
        std::string toStr();
    };

    class HttpRspMsg{
    public:
        HttpRspMsg(){}
        std::string _sVersion = "HTTP/1.1";
        std::string _sStatus = "200";
        std::string _sDescription = "ok"; 
        std::map<std::string, std::string> _mHeaders;
        std::string _sContent;
        std::string toStr();
    };

}

#endif