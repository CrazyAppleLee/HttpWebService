#ifndef HTTPMSG_H
#define HTTPMSG_H

#include <string>
#include <map>
namespace WebServer{
    class HttpReqMsg{
    public:
        HttpReqMsg(){}
        std::string _method;
        std::string _url;
        std::string _version;
        std::map<std::string, std::string> _headers; //头属性
        std::string _content;
        bool parseHttpReq(std::string msg);
    };

    class HttpRspqMsg{
    public:
        HttpRspqMsg(){}
        std::string _version = "HTTP/1.1";
        std::string _status = "200";
        std::string _description = "ok"; 
        std::map<std::string, std::string> _headers;
        std::string _content;
        std::string toStr();
    };

}

#endif