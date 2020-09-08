#include "EventLoop.h"
#include "Epoll.h"
#include "utils/Common.h"
#include <sys/epoll.h>
#include <vector>

EventLoop::EventLoop()
:   _epollPtr(new Epoll()),
    _quit(false),
    //weakupFd(createEventfd())
    //weakupChannel(new Channel(this,weakupFd))
{

}

EventLoop::~EventLoop()
{

}

void EventLoop::doLoop()
{
    std::vector<ChannelPtr> vRetChannelPtr;
    while(!_quit)
    {
        vRetChannelPtr = epollPtr->poll();
        std::vector<ChannelPtr>::iterator it;
        for( ;it != vRetChannelPtr; it++){
            (*it)->handleEvent();
        }
    }
}
void EventLoop::addToEpoll(ChannelPtr chnlPtr, int TimeOut = 0)
{
    
}


