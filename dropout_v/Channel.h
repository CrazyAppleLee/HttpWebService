#ifndef CHANNEL_H
#define CHANNEL_H

#include "Timer.h"
#include <memory>
#include <functional>

typedef std::function<void()> CallBack;
class Channel{
private:
    EventLoop *_loop;
    int _fd;
    __uint32_t _events;
    __uint32_t _retEvents;
    __uint32_t _lastEvents;

    CallBack _readHandler;
    CallBack _writeHandler;
    CallBack _errorHandler;
    CallBack _connHandler;

public: 
    Channel(EventLoop *loop);
    Channel(EventLoop *loop, int fd);
    ~Channel();
    void setFd(int fd){ _fd = fd; }
    void handleEvent();

    void handleRead()
    {
        if(readHandler){
            _readHandler();
        }
    }
    void handleConn()
    {
        if(connHandler){
            _connHandler();
        }
    }
    void handleWrite()
    {
        if(writeHandler){
            _writeHandler();
        }
    }
    void handleError()
    {
        if(errorHandler){
            _errorHandler();
        }
    }
    void setErrorHandler(CallBack cb){ _errorHandler = cb; }
    //void handleClose();
    void setReadhanedler(CallBack cb){ _readHandler = cb; }

    void setWritehanedler(CallBack cb){ _writeHandler = cb; }

    void setConnHandler(CallBack cb){ _connHandler = cb; }

    void setRetEvents(__uint32_t ev){ _retEvents = ev; }

    void setEvents(__uint32_t ev){ _events = ev; }

    bool UpdateEvents()
    {
        bool ret = (_lastEvents == _events);
        _lastEvents = _events;
        return ret;
    }
    
    __uint32_t& getEvent(){ return _events; }


    
};

typedef std::shared_ptr<Channel> ChannelPtr;

#endif