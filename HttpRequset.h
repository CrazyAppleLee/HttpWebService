#ifndef HTTPREQUSET_H
#define HTTPREQUSET_H

#include "./utils/C_Socket.h"
#include "./utils/C_SQueue.h"
#include "./utils/Channel.h"
#include "./utils/Utils.h"
#include "EpollLoop.h"
#include "HttpMsg.h"
#include "HttpMsg.h"
//#include "HttpServer.h"
#include <string>
#include <memory>
#include <functional>

namespace WebServer{
    enum ConnectState{
        CONNECTED = 0,
        DISCONNECTING,
        DISCONNECTED
    };
    enum PraseState{
        PRASE_START = 0,
        PRASE_URL_END,
        PRASE_HEADERS_END,
        PRASE_CONTENT_END,
        PRASE_ERROR
    };
    //class HttpServer;
    class HttpRequset: public std::enable_shared_from_this<HttpRequset>{
    private:

        C_Socket _cSocket;
        EpollLoop *_loop;
        HttpReqMsg _reqMsg;
        HttpRspMsg _rspMsg;
        std::weak_ptr<Channel> _chanPtr; //保存外层Channel
        ConnectState _connState;
        PraseState _praseState;
        __uint32_t *_setEventsPtr;
        HttpRequset(){}
    public:
        HttpRequset(C_Socket cSocket,EpollLoop *loop);
        void setCSocket(C_Socket cSocket){ _cSocket = cSocket;}
        void setLoop(EpollLoop *loop){ _loop = loop;}
        void setChannel(std::shared_ptr<Channel> &chanPtr)
        {
            _chanPtr = chanPtr;
            _setEventsPtr = chanPtr->getSetEventsHolder();
        }

        void connHander();
        void close();
        void readHandler(); //处理读事务
        void writeHandler(); //发送消息
        void errorHandler(); //处理错误
        void doRequset(); //处理请求
        void closeHandler();
        int getSocketFd(){ return _cSocket.getSocket(); } //套接字
        void doTest();//测试



    };
    typedef std::shared_ptr<HttpRequset> HttpRequsetPtr;
}

#endif