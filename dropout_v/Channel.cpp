#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *loop)
:   _loop(loop),
    _events(0),
    _retEvents(0);
    _lastEvents(0) 
{ 

}

Channel::~Channel(){

}

void Channel::handleEvent()
{
    _events = 0;
    if(_retEvents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        handleRead();
    }
    else if(_retEvents & EPOLLOUT)
    {
        handleWrite();
    }
    else if(_retEvents & EPOLLERR)
    {
        handleError();
    }

}