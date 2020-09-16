#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "utils/C_Socket.h"
#include "utils/C_SQueue.h"
#include "utils/C_Epoll.h"
#include "HandleThread.h"
#include "./utils/Channel.h"
#include "HttpRequset.h"
#include "utils/Notify.h"
#include <memory>

namespace WebServer{

    class HttpServer{
    private:

        C_Socket _acceptSocket; // 服务监听
        ChannelPtr _acceptChannel; // 监听 事务处理
        ChannelsQueuePtr _handleQueue; //事务处理队列

        C_EpollPtr _cEpollPtr; //epoll
        Notify _notify; //用于唤醒epoll

    public:

        HttpServer();
        void handleNewConn();
        void handleConn();
        void start();
        void runInServer(HandleEpoll cb); // 放在epoll触发之后 运行的事务
        void wakeup(){ _notify.notify(); }// 唤醒epoll

    };

}


#endif