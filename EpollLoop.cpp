#include "EpollLoop.h"
#include "./utils/Channel.h"
#include "./utils/C_Epoll.h"
#include "./utils/Notify.h"
//#include "./"

#include <memory>
#include <vector>
#include <queue>

using namespace WebServer;
using namespace std;

EpollLoop::EpollLoop()
:   _cEpollPtr(make_shared<C_Epoll>()),
    _qEpollHandlerPtr(make_shared<C_SQueue<HandleEpoll>>()),
    _notifyPtr(make_shared<Notify>()),
    _quit(false)
{
    _cEpollPtr->setWakeupChannelPtr(_notifyPtr);
}
void EpollLoop::runInLoop(HandleEpoll cb)
{
    _qEpollHandlerPtr->push(cb);
}
void EpollLoop::loop()
{
    cout << "Epoll loop..." << endl;
    while(!_quit)
    {
        vector<shared_ptr<Channel>> vChans = _cEpollPtr->poll();
        for(int i = 0; i < vChans.size(); i++){
            vChans[i]->handleEvent();
        }
        doEpollEvent();
    }
}

void EpollLoop::doEpollEvent()
{
    //cout << "doEpollEvent" << endl;
    shared_ptr<queue<HandleEpoll>> qEpollHandlerPtr = make_shared<queue<HandleEpoll>>();
    _qEpollHandlerPtr->swapQueue(qEpollHandlerPtr);
    cout << "doEpollEvent " << qEpollHandlerPtr->size() <<endl;
    while (!qEpollHandlerPtr->empty())
    {   
        HandleEpoll cb = qEpollHandlerPtr->front();
        qEpollHandlerPtr->pop();
        cb();
    }
}

void EpollLoop::quit()
{
    _quit = true;
    wakeUp();
}

void EpollLoop::wakeUp(){
    _notifyPtr->notify();
}

void EpollLoop::addEvent(ChannelPtr &chan)
{
    //cout << "addEvent" <<endl;
    _cEpollPtr->addChannelPtr(chan, chan->getSetEvents());
}
void EpollLoop::modEvent(ChannelPtr &chan)
{
    _cEpollPtr->modChannelPtr(chan, chan->getSetEvents());
}

void EpollLoop::delEvent(ChannelPtr &chan)
{
    _cEpollPtr->delChannelPtr(chan);
}

