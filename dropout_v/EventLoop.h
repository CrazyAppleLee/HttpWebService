#ifndef EVENLOOP_H
#define EVENLOOP_H

#include "Channel.h"
#include "Epoll.h"
#include <functional>
#include <memory>
#include <vector>

class EventLoop{
    public:
    EventLoop();
    ~EventLoop();
    //void runInLoop(std::function<void()>&& cb);
    void doLoop();
    void quit();
    void addToEpoll(ChannelPtr chnlPtr, int TimeOut = 0);
    void delFromEpoll(ChannelPtr chnlPtr);
    void modInEpoll(ChannelPtr chnlPtr, int TimeOut = 0);
    private:


    EpollPtr    _epollPtr;

    bool    _quit;
};
#endif