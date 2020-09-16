#include "Channel.h"

#include <sys/epoll.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;
using namespace WebServer;

Channel::Channel()
:   _handler(NULL),
    _readHandler(NULL),
    _writeHandler(NULL),
    _errorHandler(NULL),
    _connHandler(NULL),
    _httpRequset(NULL),
    _setEvents(0),
    _retEvents(0),
    _fd(-1),
    _doHandleEvent(true)
{

}
Channel::Channel(std::shared_ptr<HttpRequset> requset, CallBack handler)
:   _handler(handler),
    _readHandler(NULL),
    _writeHandler(NULL),
    _errorHandler(NULL),
    _connHandler(NULL),
    _httpRequset(requset),
    _setEvents(0),
    _retEvents(0),
    _fd(-1),
    _doHandleEvent(true)
{

}  
void Channel::handleEvent()
{
    _setEvents = 0;
    if ((_retEvents & EPOLLHUP) && !(_retEvents & EPOLLIN))
    {
        cout << "(_retEvents & EPOLLHUP) && !(_retEvents & EPOLLIN)" <<endl;
        _setEvents = 0;
        return;
    }
    if (_retEvents & EPOLLERR)
    {
        cout << "EPOLLERR" <<endl;
        if (_errorHandler) _errorHandler();
        _setEvents = 0;
        return;
    }
    if(_retEvents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        handleRead();
    }
    if(_retEvents & EPOLLOUT)
    {
        handleWrite();
    }

    handleConn();

}