#ifndef LOOPTHREAD_H
#define LOOPTHREAD_H

#include "./utils/C_Thread.h"
#include "EpollLoop.h"

namespace WebServer{
    class LoopThead{
    private:
        EpollLoop *_loop;
        C_Thread *_thread; 
        LoopThead(){}
    public:
        LoopThead(EpollLoop *loop)
        :   _loop(loop),
            _thread(new C_Thread())
        {

        }
        void run(){
            _loop->loop();
        }
        void start(){
            cout << "loop thread start" << endl;
            _thread->setRunFun(bind(&LoopThead::run, this));
            _thread->start();
        }
        void join(){
            _thread->join();
        }
        void quit(){
            _loop->quit();
        }
        void wakeUp(){
            _loop->wakeUp();
        }
    };
}

#endif