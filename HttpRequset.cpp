#include "HttpRequset.h"
#include "./utils/Channel.h"
#include "./utils/Utils.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace WebServer;
using namespace std;

HttpRequset::HttpRequset()
:   _cSocket(C_Socket(-1)),
    _server(NULL),
    _cEpollPtr(NULL)
{

}

HttpRequset::HttpRequset(C_Socket cSocket)
:   _cSocket(cSocket),
    _server(NULL),
    _cEpollPtr(NULL)
{

}

void HttpRequset::doTest()
{
    cout << "test http requset" <<endl;
}

void HttpRequset::connHander()
{

}
void HttpRequset::readHandler()
{
    string msg;
    //C_Socket newSocket(newChan->getFd());
    cout << "readhandle" << endl;
    bool zero = false;
    //setFdNonBlock(newSocket.getSocket());
    _cSocket.readnSocket(msg, zero);
    if(zero){
        
        _server->runInServer(bind(&C_Epoll::delChannelPtr, _cEpollPtr, _chanPtr.lock()));
        _cSocket.closeSocket();
        return ;
    }
    doRequset(msg);
    // cout << " -------zero------ " << zero << " -----------------" << endl;
    // cout << msg << endl;
    // cout << "----------------Http Msg---------------- "<< endl;

    // ostringstream rsp;
    // static int count = 0;
    // rsp << "HTTP/1.1 200 OK\r\n";
    // //rsp +=          "Content-Type: text/plain\r\n";
    // rsp << "\r\n";
    // rsp << "<html>";
    // rsp << "index page " << count;
    // count ++;
    // rsp << "</html>";
    // string str(rsp.str());

    // _cSocket.writenSocket(str);
    // _server->runInServer(bind(&C_Epoll::delChannelPtr, _cEpollPtr, _chanPtr.lock()));
    // _cSocket.closeSocket();

    //_cEpollPtr->delChannelPtr(_chanPtr.lock());
}

void HttpRequset::doRequset(string reqMsg)
{
    HttpReqMsg httpReq= parseHttpReq(reqMsg);
    cout << reqMsg <<endl;
    cout << "HttpReqMsg parseHttpReq" << endl ;
    cout << httpReq.method << " " << httpReq.url << " " << httpReq.version << endl;
    map<string, string>::iterator it = httpReq.header.begin();
    for(; it != httpReq.header.end(); it++)
    {
        cout << it->first << " " << it->second <<endl;
    }
    cout << httpReq.content << endl;
}


void HttpRequset::writeHandler()
{
    
    _server->runInServer(bind(&C_Epoll::delChannelPtr, _cEpollPtr, _chanPtr.lock()));
    _cSocket.closeSocket();
}
/*
struct HtttpReqMsg{
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string, std::string> header;
    std::string content;
}
*/
HttpReqMsg HttpRequset::parseHttpReq(std::string msg){
    HttpReqMsg hMsgReq;
    vector<string> vString = split(msg, "\r\n");
    if(vString.size() < 2) return hMsgReq;
    vector<string> vtmp = split(vString[0], " ");
    hMsgReq.method = vtmp[0];
    hMsgReq.url = vtmp[1];
    hMsgReq.version = vtmp[2];
    //int i=1;
    for(int i = 1; i < vString.size(); i++)
    {
        if(vString[i] == "") break;
        vtmp = split(vString[i], ":");
        if(vtmp.size() < 2) continue;
        hMsgReq.header[vtmp[0]] = vtmp[1];
    }
    hMsgReq.content = vString[vString.size() - 1];
    return hMsgReq;
}