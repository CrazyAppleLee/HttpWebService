#ifndef NOTIFY_H
#define NOTIFY_H

#include <iostream>
#include <sys/eventfd.h>
#include <unistd.h>
#include <memory>
namespace WebServer{

    class Notify{
    private:
        int _wakeUpFd;
        bool _isNotified; //已经通知
    public:
        Notify()
        :   _wakeUpFd(eventfd(0, EFD_CLOEXEC)),
            _isNotified(false)
        {
        }
        void wait(){
            uint64_t rInt = 0;
            ssize_t num = read(_wakeUpFd, &rInt, sizeof(rInt));
            
            if(num < 0) {
                std::cout << "Notify: wait error" << std::endl;
            }
            _isNotified = false;
        }
        void notify(){
            if(_isNotified) return ;
            uint64_t wInt = 1;
            ssize_t num = write(_wakeUpFd, &wInt, sizeof(wInt));
            if(num < 0) {
                std::cout << "Notify: notify error" << std::endl;
            }
            _isNotified = true;
        }
    };
    typedef std::shared_ptr<Notify> NotifyPtr;
}
#endif