#include "HandleThread.h"
#include "utils/Channel.h"
#include <iostream>

using namespace WebServer;
using namespace std;

void HandleThread::start(){
    _thread.setRunFun(bind(&HandleThread::run, this));
    _thread.start();
}
void HandleThread::run(){
    ChannelPtr chan;
    //cout << "HandleThread run "<<endl;
    while(true)
    {
        {
            C_MutexLockGuard lock(_mLock);
            if(_quit) break;
        }
        //cout << "_chansQueuePtr pop "<<endl;
        //WebServer::C_SQueue<std::shared_ptr<WebServer::Channel> >::push(WebServer::Channel&)
        while(_chansQueuePtr->pop(chan))
        {
            {
                C_MutexLockGuard lock(_mLock);
                if(_quit) break;
            }
            chan->handle();
        }
        _notifyPtr->wait();
    }
}
void HandleThread::quit(){
    
    C_MutexLockGuard lock(_mLock);
    _quit = true;
    
}