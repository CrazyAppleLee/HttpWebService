#ifndef C_EPOLL_H
#define C_EPOLL_H

#include "C_SQueue.h"
#include "Channel.h"
#include "Notify.h"
#include <sys/epoll.h>
#include <vector>
#include <functional>

//#include <map>

namespace WebServer{

    template <typename T> class C_SQueue;
    class Channel;
    // typedef std::shared_ptr<Channel> ChannelPtr;
    // typedef C_SQueue<ChannelPtr> ChannelsQueue;
    // typedef std::shared_ptr<ChannelsQueue> ChannelsQueuePtr;

    class C_Epoll{
    private:
        static const int MAXFDS = 65535;        //描述符的范围 
        static const int EVENTSIZE = 2048;
        static const int EPOLLWAIT_TIME = -1;
        int _epollFd;                           //epoll的描述符
        std::shared_ptr<Channel> _socket2ChannelPtr[MAXFDS];  //socket描述符到Channel的映射。
        std::vector<epoll_event> _events;
        std::shared_ptr<Channel> _wakeupChan;

    public:
        C_Epoll();
        void setWakeupChannelPtr(std::shared_ptr<Channel> newChanPtr);
        void setWakeupChannelPtr(NotifyPtr notifyPtr);
        void addChannelPtr(std::shared_ptr<Channel> newChanPtr, __int32_t setEvents); //添加监听事件
        void delChannelPtr(std::shared_ptr<Channel> delChanPtr); //删除监听事件
        void modChannelPtr(std::shared_ptr<Channel> modChanPtr, __int32_t setEvents); //修改状态
        std::vector<std::shared_ptr<Channel>> poll();
    };
    typedef std::shared_ptr<C_Epoll> C_EpollPtr;
    typedef std::function<void()> HandleEpoll; //处理epoll事务的函数 类型
    typedef std::shared_ptr<C_SQueue<HandleEpoll>> HandleEpollQueuePtr;//处理epoll事务的函数队列  类型

}

#endif