#include "HttpServer.h"
#include "utils/Utils.h"
#include "utils/C_Socket.h"
#include "utils/Channel.h"
#include "HandleThread.h"
#include "HttpRequset.h"

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
    cout << "server start " << endl;
    _acceptChannel->setFd(_acceptSocket.getSocket());
    _acceptChannel->setReadhanedler(bind(&HttpServer::handleNewConn, this));
    _acceptChannel->setConnHandler(bind(&HttpServer::handleConn, this));
    _acceptChannel->setSetEvents(EPOLLIN|EPOLLET);
    _cEpollPtr->addChannelPtr(_acceptChannel, _acceptChannel->getSetEvents()); //监听新连接channel

    _cEpollPtr->setWakeupChannelPtr(_notifyPtr); //可以被唤醒

    _handleEpoll->setNotifyFun(bind(&HttpServer::wakeup, this)); //在_handleEpoll中添加事务 唤醒本服务(线程)。

    _handleEventThreadPtr->setQueuePtr(_handleQueue);
    _handleQueue->setNotifyFun(bind(&HandleThread::wakeup, _handleEventThreadPtr));
    //_handleEventThreadPtr->start();
    //cout << "_handleEventThread start " << endl;  
    while(true){
        vector<ChannelPtr> vActiveChannel = _cEpollPtr->poll();
        cout << "IO happened" << endl;
        //_handleQueue->pushVector(vActiveChannel);
        for(int i = 0; i < vActiveChannel.size(); i++)
        {
            vActiveChannel[i]->handleEvent();
        }
        handleEpoll();
    }
}

void HttpServer::handleConn(){

}

void HttpServer::handleNewConn(){
    cout << "handleNewConn" << endl;
    C_Socket newSocket;
    _acceptSocket.acceptConn(newSocket);
    cout << "acceptConn fd " << newSocket.getSocket() << endl;
    setFdNonBlock(newSocket.getSocket());
    
    ChannelPtr newChan = make_shared<Channel>();

    HttpRequsetPtr newReuset = make_shared<HttpRequset>();
    newReuset->setCSocket(newSocket);
    newReuset->setChannel(newChan);
    newReuset->setCEpoll(_cEpollPtr);
    newReuset->setServer(this);

    newChan->setFd(newSocket.getSocket());
    newChan->setReadhanedler(bind(&HttpRequset::readHandler,newReuset));
    newChan->setWritehanedler(bind(&HttpRequset::writeHandler,newReuset));
    newChan->setConnHandler(bind(&HttpRequset::connHander,newReuset));
    newChan->setSetEvents(EPOLLIN|EPOLLET);
    runInServer(bind(&C_Epoll::addChannelPtr, _cEpollPtr, newChan,newChan->getSetEvents()));


}

void HttpServer::runInServer(HandleEpoll cb){
    _handleEpoll->push(cb);
}

void HttpServer::handleEpoll(){
    shared_ptr<queue<HandleEpoll>> HQueue = make_shared<queue<HandleEpoll>>();
    _handleEpoll->swapQueue(HQueue);
    cout << "handleEpoll" << HQueue->size() <<endl;
    while (!HQueue->empty())
    {   
        HandleEpoll cb = HQueue->front();
        HQueue->pop();
        cb();
    }
}