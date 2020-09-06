#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include<memory>
#include <vector>

class Epoll{
public:
    Epoll();
    ~Epoll();
    void epollAdd(ChannelPtr chnlPtr, int timeOut = 0);
    void epollMod(ChannelPtr chnlPtr, int timeOut = 0);
    void epollDel(ChannelPtr chnlPtr);
    std::vector<ChannelPtr> poll();
    std::vector<ChannelPtr> getEventsRequest(int events_num);
    //void add_timer(ChannelPtr chnlPtr, int timeOut);
    int getEpollFd()
    {
        return epollFd_;
    }
private:
    const int MAXFDS = 100000;
    int epollFd_;
    std::vector<epoll_event> events;
    ChannelPtr arrFd2ChanPtr[MAXFDS];
    //TimerManager timerManager;

};
typedef std::share<Epoll> EpollPtr;

#endif
