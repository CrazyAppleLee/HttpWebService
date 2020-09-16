#ifndef HTTPREQUSET_H
#define HTTPREQUSET_H

#include "./utils/C_Socket.h"
#include "./utils/C_SQueue.h"
#include "./utils/Channel.h"
#include "HttpServer.h"
#include <string>
#include <memory>

namespace WebServer{
    class HttpServer;
    class HttpRequset: public std::enable_shared_from_this<HttpRequset>{
    private:

        C_Socket _cSocket;
        HttpServer *_server;
        //C_EpollPtr _cEpollPtr;
        std::string _reqMsg;
        std::string _rspMsg;
        std::weak_ptr<Channel> _chanPtr; //保存外层Channel
        
    public:

        HttpRequset();
        HttpRequset(C_Socket cSocket);
        void setServer(HttpServer *server){ _server = server;}
        void setChannel(std::weak_ptr<Channel> chanPtr){_chanPtr = chanPtr;}

        void connHander();
        void close();
        void readHandler(); //处理读事务
        void writeHandler(); //发送消息
        void errorHandler(); //处理错误
        void doRequset(); //处理请求
        int getSocketFd(){ return _cSocket.getSocket(); } //套接字
        void doTest();//测试

    };
}

#endif