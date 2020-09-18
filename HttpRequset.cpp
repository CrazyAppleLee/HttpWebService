#include "HttpRequset.h"
#include "./utils/Channel.h"
#include "./utils/Utils.h"

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
    HttpReqMsg httpReq;
    if(!httpReq.parseHttpReq(reqMsg)) {
        errorHandler();
    }
    cout << reqMsg <<endl;
    cout << "HttpReqMsg parseHttpReq" << endl ;
    cout << httpReq.method << " " << httpReq.url << " " << httpReq.version << endl;
    map<string, string>::iterator it = httpReq.headers.begin();
    for(; it != httpReq.headers.end(); it++)
    {
        cout << it->first << " " << it->second <<endl;
    }
    cout << httpReq.content << endl;


    HttpRspqMsg httpRsp;
    string pageContent;
    if(readWebPage(httpReq.url, pageContent)){
        httpRsp.content = pageContent;
    }
    else {
        httpRsp.status = "404";
        httpRsp.description = "not found";
        httpRsp.content = "<html><h1>not found</h1></html>";
    }
    httpRsp.headers["Content-type"] = "text/html";
    string rspMsg = httpRsp.toStr();
    cout << rspMsg << endl;
    _msgRsqQueue.push(httpRsp);
    ChannelPtr tmpChan = _chanPtr.lock();
    tmpChan->setSetEvents(tmpChan->getSetEvents()|EPOLLOUT);
    _server->runInServer(bind(&C_Epoll::modChannelPtr, _cEpollPtr, tmpChan, tmpChan->getSetEvents()));
    //_cSocket.writenSocket(rspMsg);
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
    // _server->runInServer(bind(&C_Epoll::delChannelPtr, _cEpollPtr, _chanPtr.lock()));
    // _cSocket.closeSocket();
}
void HttpRequset::errorHandler()
{

}
