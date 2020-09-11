#ifndef C_MUTEXLOCK_H
#define C_MUTEXLOCK_H
#include <pthread.h>

namespace WebServer{
    class C_MutexLock{
    private:
        pthread_mutex_t _iLock;

    public:
        C_MutexLock()
        {
            pthread_mutex_init(&_iLock, NULL);
        }

        

        void lockThread()
        {
            pthread_mutex_lock(&_iLock);
        }

        void unLockThread()
        {
            pthread_mutex_unlock(&_iLock);
        }
        
        ~C_MutexLock()
        {
            pthread_mutex_lock(&_iLock);
            pthread_mutex_destroy(&_iLock);
        }

    };

    class C_MutexLockGuard{
    private:
        C_MutexLock &_mutexLock;

    public:
        explicit C_MutexLockGuard(C_MutexLock &mlock): _mutexLock(mlock)
        {
            _mutexLock.lockThread();
        }
        ~C_MutexLockGuard(){
            _mutexLock.unLockThread();
        }
    };
}
#endif