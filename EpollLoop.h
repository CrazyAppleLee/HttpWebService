#ifndef EPOLLLOOP_H
#define EPOLLLOOP_H

#include "./utils/Notify.h"
#include "./utils/Channel.h"
#include "./utils/C_Epoll.h"
#include "./utils/C_SQueue.h"
#include "./utils/C_Socket.h"
//#include <memory>

namespace WebServer{
    
    class EpollLoop{
    private:
        C_EpollPtr _cEpollPtr;
        HandleEpollQueuePtr _qEpollHandlerPtr;
        NotifyPtr _notifyPtr;
        bool _quit;
    public:
        EpollLoop();
        void runInLoop(HandleEpoll cb);
        void loop();
        void doEpollEvent();
        void quit();
        void wakeUp();

        void addEvent(ChannelPtr &chan);
        void modEvent(ChannelPtr &chan);
        void delEvent(ChannelPtr &chan);
    }; 
}


#endif