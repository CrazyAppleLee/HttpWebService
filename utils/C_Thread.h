#ifndef C_THREAD_H
#define C_THREAD_H
#include <pthread.h>
#include <functional>

namespace WebServer{
    //typedef std::function<void()> Function;
    class C_Thread{
    private:
        typedef std::function<void()> Function;
        bool   _bStarted;
        bool   _bJoin; 
        pthread_t   _pId;
        Function    _runFun;
        C_Thread(){};
        //void *run(void *);

    public:

        C_Thread(Function runFun);
        bool start();
        bool join();
        void run();
        
        
    };
}
#endif