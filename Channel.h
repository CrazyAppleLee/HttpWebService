#ifndef CHANNEL_H
#define CHANNEL_H

#include "Timer.h"
#include <memory>

class Channel{
private:
    EventLoop *loop;
    int fd;
    _uint32_t events;
    _uint32_t retEvents;
    _uint32_t lastEvents;

public:
    //typedef 
    Channel(EventLoop *loop);
    Channel(EventLoop *loop, int fd);
    ~Channel();
    void handleEvent();

    void handleRead();
    void handleConn();
    void handleClose();
    void handleError();
    
};

typedef std::shared_ptr<Channel> ChannelPtr;

#endif