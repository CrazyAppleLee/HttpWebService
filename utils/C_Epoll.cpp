#include "C_Epoll.h"

#include "Channel.h"
#include <sys/epoll.h>
#include <iostream>

using namespace WebServer;
using namespace std;


C_Epoll::C_Epoll()
:   _epollFd(epoll_create1(EPOLL_CLOEXEC)),
    _events(EVENTSIZE)
{

}

void C_Epoll::setWakeupChannelPtr(std::shared_ptr<Channel> newChanPtr)
{
    _wakeupChan = newChanPtr;
    addChannelPtr(_wakeupChan, _wakeupChan->getSetEvents());
}
void C_Epoll::setWakeupChannelPtr(NotifyPtr notifyPtr)
{
    _wakeupChan = make_shared<Channel>();
    _wakeupChan->setFd(notifyPtr->getFd());
    _wakeupChan->setReadHanedler(bind(&Notify::wait, notifyPtr));
    _wakeupChan->setSetEvents(EPOLLIN|EPOLLET);
    addChannelPtr(_wakeupChan, _wakeupChan->getSetEvents());
}

void C_Epoll::addChannelPtr(ChannelPtr addChanPtr, __int32_t setEvents)
{
    int socketFd = addChanPtr->getFd();

    //cout << "start addChannelPtr socketFd = " << socketFd << endl;
    struct epoll_event event;
    event.data.fd = socketFd;
    event.events = setEvents;
    if(epoll_ctl(_epollFd, EPOLL_CTL_ADD, socketFd, &event) !=0){
        
        return ;
    }
    _socket2ChannelPtr[socketFd] = addChanPtr;
    //cout <<_socket2ChannelPtr<< " end addChannelPtr socketFd = " << socketFd << " chanPtr "<< addChanPtr << " " << _socket2ChannelPtr[socketFd] << endl;
    return ;
}

void C_Epoll::delChannelPtr(ChannelPtr delChanPtr)
{
    int socketFd = delChanPtr->getFd();
    cout << "del fd " << socketFd <<endl;
    if(epoll_ctl(_epollFd, EPOLL_CTL_DEL, socketFd, NULL) != 0){
        return ;
    }
    _socket2ChannelPtr[socketFd].reset();

    return ;
}

void C_Epoll::modChannelPtr(ChannelPtr modChanPtr, __int32_t setEvents)
{
    int socketFd = modChanPtr->getFd();
    struct epoll_event event;
    event.data.fd = socketFd;
    event.events = setEvents;
    if(epoll_ctl(_epollFd, EPOLL_CTL_MOD, socketFd, &event) !=0){
        
        return ;
    }
    return ;
}

vector<ChannelPtr> C_Epoll::poll()
{
    vector<ChannelPtr> acceptChanPtr;
    //_events.clear();
    int epNum = 0;
    epNum = epoll_wait(_epollFd, &*_events.begin(), _events.size(), EPOLLWAIT_TIME);
    if(epNum < 0)
    {
         return acceptChanPtr;
    }
    ChannelPtr tmpChan;
    int wakeupFd = -1; 
    if(_wakeupChan){
        wakeupFd =  _wakeupChan->getFd();
    } 
    for(int i = 0; i < epNum; i++)
    {
        if(_events[i].data.fd == wakeupFd){ //被唤醒的 马上处理
            _wakeupChan->handleRead();
            continue;
        }
        tmpChan = _socket2ChannelPtr[_events[i].data.fd];
        //cout <<_socket2ChannelPtr<< " event fd "<< _events[i].data.fd << " tmpChan " << tmpChan << " " << _socket2ChannelPtr[5] << endl;
        tmpChan->setRetEvents(_events[i].events);
        acceptChanPtr.push_back(tmpChan);
    }
    return acceptChanPtr;
}
