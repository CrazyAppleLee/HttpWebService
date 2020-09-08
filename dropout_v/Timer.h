#ifndef TIME_H
#define TIME_H
#include <memory>
#include <queue>
#include "Channel.h"

class Channel;

class Timer{
public:
    Timer(ChannelPtr chnlPtr, int timeOut);    
    ~Timer();

    void setTimer();
private:
    //int timtOut;
    int expiredTime_;
};
typedef std::share_ptr<Timer> TimePtr;
class TimerManager{
public:
    TimerManager();
    ~TimerManager();

private:
    queue<Timer> timerQueue;
};

#endif