#include "EventLoop.h"
#include "Epoll.h"
#include "utils/Common.h"
#include <sys/epoll.h>
#include <vector>

EventLoop::EventLoop()
:   epollPtr(new Epoll()),
    quit_(false),
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
    while(!quit_)
    {
        vRetChannelPtr = epollPtr->poll();
        std::vector<ChannelPtr>::iterator it;
        for( ;it != vRetChannelPtr; it++){
            (*it)->handleEvent();
        }
    }
}


