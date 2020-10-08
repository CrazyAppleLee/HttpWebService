#include "HttpRequset.h"
#include "./utils/Channel.h"
#include "./utils/Utils.h"
#include "./HttpMsg.h"

#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace WebServer;
using namespace std;

HttpRequset::HttpRequset()
:   _cSocket(C_Socket(-1)),
    _loop(NULL),
    _cEpollPtr(NULL)
{

}

HttpRequset::HttpRequset(C_Socket cSocket)
:   _cSocket(cSocket),
    _loop(NULL),
    _cEpollPtr(NULL)
{

}

void HttpRequset::doTest()
{
    cout << "test http requset" <<endl;
}

void HttpRequset::connHander()
{
    if(_bClose){
        _loop->runInLoop(bind(&EpollLoop::delEvent, _loop, _chanPtr.lock()));
    }
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
        _bClose = true;
        //_loop->runInLoop(bind(&EpollLoop::delEvent, _loop, _chanPtr.lock()));
        //_cSocket.closeSocket();
        return ;
    }

    doRequset(msg);
}

void HttpRequset::doRequset(string reqMsg)
{
    // HttpReqMsg httpReq;
    // if(!httpReq.parseHttpReq(reqMsg)) {
    //     errorHandler();
    // }
    // cout << reqMsg <<endl;
    // cout << "HttpReqMsg parseHttpReq" << endl ;
    // cout << httpReq.method << " " << httpReq.url << " " << httpReq.version << endl;
    // map<string, string>::iterator it = httpReq.headers.begin();
    // for(; it != httpReq.headers.end(); it++)
    // {
    //     cout << it->first << " " << it->second <<endl;
    // }
    // cout << httpReq.content << endl;


    HttpRspqMsg httpRsp;
    // if(httpReq.url != "/upload"){
    string pageContent;
    if(readWebPage("/", pageContent))
    //{
        httpRsp._content = pageContent;
    // }
    // else {
    //     httpRsp.status = "404";
    //     httpRsp.description = "not found";
    //     httpRsp.content = "<html><h1>not found</h1></html>";
    // }
    // }
    // httpRsp.headers["Content-type"] = "text/html";
    string rspMsg = httpRsp.toStr();
    cout << rspMsg << endl;
    _msgRsqQueue.push(httpRsp);
    writeHandler();
}


void HttpRequset::writeHandler()
{
    shared_ptr<queue<HttpRspqMsg>> quePtr = make_shared<queue<HttpRspqMsg>>();
    _msgRsqQueue.swapQueue(quePtr);
    while(!quePtr->empty())
    {
        HttpRspqMsg rsp = quePtr->front();
        quePtr->pop();
        string rspMsg = rsp.toStr();
        _cSocket.writenSocket(rspMsg);
    }
    //_server->runInServer(bind(&C_Epoll::delChannelPtr, _cEpollPtr, _chanPtr.lock()));
    //_cSocket.closeSocket();
}
void HttpRequset::errorHandler()
{

}
