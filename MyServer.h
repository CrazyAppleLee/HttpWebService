#ifndef MYSERVER_H
#define MYSERVER_H

#include "./utils/Channel.h"
#include "EpollLoop.h"
#include "LoopThreadPool.h"

namespace WebServer{

    class MyServer{
    private:
        EpollLoop *_mainLoop;
        LoopThreadPool *_loopPool;
        C_Socket _acSocket;
        ChannelPtr _acChannelPtr;
        MyServer(){}
    public:
        MyServer(EpollLoop *loop, LoopThreadPool *loopPool, int port);
        void handleNewConn();
        void handleConn();
        void start();
    };
}
#endif