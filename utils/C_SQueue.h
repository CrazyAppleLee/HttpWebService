#ifndef C_SQUEUE_H
#define C_SQUEUE_H

#include "C_MutexLock.h"
#include <queue>
#include <memory>

namespace WebServer{
    template <typename T>
    class C_SQueue{
    private:
        std::shared_ptr<std::queue<T>> _queue;
        C_MutexLock _mLock;

    public:
        C_SQueue()
        :   _queue(new std::queue<T>())
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
        bool push(const T &e)
        {
            {
                C_MutexLockGuard lock(_mLock);
                _queue->push(e);
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

    };
}
#endif