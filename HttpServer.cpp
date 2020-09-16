#include "HttpServer.h"
#include "utils/Utils.h"
#include "utils/C_Socket.h"
#include "utils/Channel.h"
#include "HandleThread.h"

#include <memory>
#include <functional>


using namespace std;
using namespace WebServer;

HttpServer::HttpServer(int port)
:   _acceptChannel(make_shared<Channel>()),
    _handleEventThreadPtr(new HandleThread()),
    _handleQueue(make_shared<ChannelsQueue>()),
    _cEpollPtr(make_shared<C_Epoll>()),
    _handleEpoll(make_shared<C_SQueue<HandleEpoll>>()),
    _notifyPtr(make_shared<Notify>())
{
    _acceptSocket.setPort(port);
    if(!_acceptSocket.createSocket()){
        cout << "createSocket error" << endl;
    }
    _acceptSocket.setSoReuseAddr();
    setFdNonBlock(_acceptSocket.getSocket());
    //cout<< cSocket.getLocalIp()<<endl;
    if(!_acceptSocket.bindSocket()){
        cout << "bindSocket error" << endl;
    }
    if(!_acceptSocket.listenSocket()){
        cout << "listenSocket error" << endl;
    }
    //_acceptChannel = make_shared<Channel>();
    //_acceptChannel
}
void HttpServer::start()
{
    _acceptChannel->setFd(_acceptSocket.getSocket());
    _acceptChannel->setReadhanedler(bind(&HttpServer::handleNewConn, this));
    _acceptChannel->setConnHandler(bind(&HttpServer::handleConn, this));
    _acceptChannel->setSetEvents(EPOLLIN|EPOLLET);
    _cEpollPtr->addChannelPtr(_acceptChannel, _acceptChannel->getSetEvents()); //监听新连接channel

    _cEpollPtr->setWakeupChannelPtr(_notifyPtr); //可以被唤醒

    _handleEpoll->setNotifyFun(bind(&HttpServer::wakeup, this)); //在_handleEpoll中添加事务 唤醒本服务(线程)。

    _handleEventThreadPtr->setQueuePtr(_handleQueue);
    _handleQueue->setNotifyFun(bind(&HandleThread::wakeup, _handleEventThreadPtr));
    _handleEventThreadPtr->start();
    while(true){
        vector<ChannelPtr> vActiveChannel = _cEpollPtr->poll();
        _handleQueue->pushVector(vActiveChannel);
        handleEpoll();
    }
}

void HttpServer::handleConn(){

}

void HttpServer::handleNewConn(){

}

void HttpServer::runInServer(HandleEpoll cb){
    _handleEpoll->push(cb);
}

void HttpServer::handleEpoll(){

}