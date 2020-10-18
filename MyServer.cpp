#include "MyServer.h"
#include "./utils/Utils.h"
#include "./utils/C_Socket.h"
#include "./utils/Channel.h"
#include "LoopThreadPool.h"
#include "HttpRequset.h"

#include <memory>

using namespace WebServer;
using namespace std;

MyServer::MyServer(EpollLoop *loop, LoopThreadPool *loopPool, int port = 10088)
:   _mainLoop(loop),
    _loopPool(loopPool),
    _acSocket(),
    _acChannelPtr(make_shared<Channel>())
{
    //cout << _mainLoop << " "<< _loopPool << endl;
    //cout << "init server" << endl;
    _acSocket.setPort(port);
    //cout << _acSocket.getPort() << endl;
    if(!_acSocket.createSocket()){
        cout << "create socket fd error" << endl;
    }
    if(!_acSocket.bindSocket()){
        cout << "bindSocket error" << endl;
    }
    _acSocket.setSoReuseAddr();
    setFdNonBlock(_acSocket.getSocket());
    _acSocket.listenSocket();
    _acChannelPtr->setFd(_acSocket.getSocket());
    _acChannelPtr->setReadHanedler(bind(&MyServer::handleNewConn, this));
    _acChannelPtr->setConnHandler(bind(&MyServer::handleConn, this));
    _acChannelPtr->setSetEvents(EPOLLIN|EPOLLET);
    //EpollLoop *loop = _loopPool->getLool();
    _mainLoop->addEvent(_acChannelPtr);
}
void MyServer::start()
{
    //cout << _mainLoop << " "<< _loopPool << endl;
    //cout << "server start" << endl;
    _loopPool->start();
    _loopPool->join();
}
void MyServer::handleNewConn()
{
    cout << "new Connect" << endl;
    C_Socket newSocket; 
    _acSocket.acceptConn(newSocket);
    setFdNonBlock(newSocket.getSocket());
    ChannelPtr newChanPtr = make_shared<Channel>();
    EpollLoop *loop = _loopPool->getLoop();
    newChanPtr->setFd(newSocket.getSocket());
    shared_ptr<HttpRequset> newReqPtr = make_shared<HttpRequset>(newSocket,loop);
    // newReqPtr->setLoop(loop);
    // newReqPtr->setCSocket(newSocket);
    newChanPtr->setHolder(newReqPtr);
    newChanPtr->setReadHanedler(bind(&HttpRequset::readHandler, newReqPtr));
    newChanPtr->setWriteHanedler(bind(&HttpRequset::writeHandler, newReqPtr));
    newChanPtr->setConnHandler(bind(&HttpRequset::connHander, newReqPtr));
    newChanPtr->setSetEvents(EPOLLIN|EPOLLET);
    newReqPtr->setChannel(newChanPtr);
    loop->runInLoop(bind(&EpollLoop::addEvent, loop, newChanPtr));
}
void MyServer::handleConn()
{
    _acChannelPtr->setSetEvents(EPOLLIN|EPOLLET);
    _mainLoop->modEvent(_acChannelPtr);
}