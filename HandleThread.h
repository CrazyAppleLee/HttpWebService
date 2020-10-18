#ifndef HANLETHREAD_H
#define HANLETHREAD_H

#include "utils/C_Thread.h"
#include "utils/C_MutexLock.h"
#include "utils/Channel.h"
#include "utils/C_SQueue.h"
#include "utils/Notify.h"
#include <memory>
#include <functional>

namespace WebServer{
    
    class HandleThread{
    private:
        bool _quit = false;
        C_Thread _thread;
        C_MutexLock _mLock;
        ChannelsQueuePtr _chansQueuePtr;
        NotifyPtr _notifyPtr;
        
        void run();

    public:
        HandleThread():_notifyPtr(std::make_shared<Notify>())
        {

        }
        HandleThread(ChannelsQueuePtr chansQueuePtr){_chansQueuePtr = chansQueuePtr;}
        void setQueuePtr(ChannelsQueuePtr chansQueuePtr){_chansQueuePtr = chansQueuePtr;}
        void start();
        
        void quit();
        void wakeup(){ _notifyPtr->notify(); }

    };
    typedef std::shared_ptr<HandleThread> HandleThreadPtr;
}
#endif