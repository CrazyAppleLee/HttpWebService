#ifndef HANLETHREAD_H
#define HANLETHREAD_H

#include "utils/C_Thread.h"
#include "utils/C_MutexLock.h"
#include "utils/C_SQueue.h"
#include "Channel.h"
#include <memory>
#include <functional>

namespace WebServer{

    typedef std::shared_ptr<C_SQueue<Channel>> ChannelsQueuePtr;

    class HandleThread{
    private:
        bool _quit = false;
        C_Thread _thread;
        C_MutexLock _mLock;
        ChannelsQueuePtr _chansQueuePtr;


    public:
        HandleThread(){}
        HandleThread(ChannelsQueuePtr chansQueuePtr){_chansQueuePtr = chansQueuePtr;}
        void setQueuePtr(ChannelsQueuePtr chansQueuePtr){_chansQueuePtr = chansQueuePtr;}
        void start();
        void run();
        void quit();

    };
}
#endif