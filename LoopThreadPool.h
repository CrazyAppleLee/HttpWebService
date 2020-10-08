#ifndef LOOPTHREADPOOL_H
#define LOOPTHREADPOOL_H

#include "./utils/C_Thread.h"
#include "LoopThread.h"

#include <vector>

namespace WebServer{

    class LoopThreadPool{
    private:
        EpollLoop *_mainLoop;
        std::vector<EpollLoop*> _vLoop;
        std::vector<LoopThead> _vThead;
        int _tNum; //线程数量
        int _iNextPool;
    public:
        LoopThreadPool(EpollLoop *mainLoop)
        :   _mainLoop(mainLoop),
            _tNum(3),
            _iNextPool(0)
        {

        }
        void setThreadNun(int num){ _tNum = num; }
        void start()
        {
            cout << "loop thread pool start" << endl;
            LoopThead mainThread(_mainLoop);
            _vLoop.push_back(_mainLoop);
            _vThead.push_back(mainThread);

            for(int i = 1; i < _tNum; i++)
            {
                EpollLoop *loop = new EpollLoop();
                LoopThead thread(loop);
                _vLoop.push_back(loop);
                _vThead.push_back(thread);
            }
            for(int i = 0; i < _tNum; i++)
            {
                _vThead[i].start();
            }
        }
        void join(){
            for(int i = 0; i < _tNum; i++)
            {
                _vThead[i].join();
            }
        }
        void quit()
        {
            for(int i = 0; i < _tNum; i++)
            {
                _vThead[i].quit();
            }
        }
        void wakeUp()
        {
            for(int i = 0; i < _tNum; i++)
            {
                _vThead[i].wakeUp();
            }
        }
        EpollLoop* getLoop(){
            _iNextPool = _iNextPool % _vLoop.size();
            return _vLoop[_iNextPool++];
        }
    };
}
#endif