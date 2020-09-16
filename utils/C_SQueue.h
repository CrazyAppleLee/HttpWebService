#ifndef C_SQUEUE_H
#define C_SQUEUE_H

#include "C_MutexLock.h"
#include "Notify.h"
#include <vector>
#include <queue>
#include <memory>
#include <functional>

namespace WebServer{
    template <typename T>
    class C_SQueue{
    private:
        std::shared_ptr<std::queue<T>> _queue;
        C_MutexLock _mLock;
        std::function<void()> _notifyFun;

    public:
        C_SQueue()
        :   _queue(new std::queue<T>()),
            _notifyFun(NULL)
        {

        }
        bool pop(T &e)
        {
            {
                C_MutexLockGuard lock(_mLock);
                if(_queue->empty()) return false;
                e = _queue->front();
                _queue->pop();
            }
            return true;
        }
        // bool push(const T &e)
        // {
        //     {
        //         C_MutexLockGuard lock(_mLock);
        //         _queue->push(e);
        //     }
        //     return true;
        // }
        bool push(T &e)
        {
            {
                C_MutexLockGuard lock(_mLock);
                _queue->push(e);
            }
            return true;
        }
        bool push(T &&e)
        {
            {
                C_MutexLockGuard lock(_mLock);
                _queue->push(e);
            }
            if(_notifyFun){
                _notifyFun();
            }
            return true;
        }
        bool pushVector(std::vector<T> &v)
        {
            if(v.empty()) 
                return true;
            {
                C_MutexLockGuard lock(_mLock);
                for(int i = 0; i < v.size(); i++){
                    _queue->push(v[i]);
                }
            }
            if(_notifyFun){
                _notifyFun();
            }
            return true;
        }
        bool empty()
        {
            {
                C_MutexLockGuard lock(_mLock);
                if(_queue->empty()) return true;
            }
            return false;
        }
        
        void swapQueue(std::shared_ptr<std::queue<T>> &newQueue)
        {
            std::shared_ptr<std::queue<T>> tmpQ;
            {
                C_MutexLockGuard lock(_mLock);
                tmpQ = _queue;
                _queue = newQueue;
            }
            //newQueue = tmpQ;
            
        }

    };
}
#endif