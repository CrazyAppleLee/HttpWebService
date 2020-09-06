#ifndef COMMON_H
#define COMMON_H
#include <functional>
#include <sys/epoll.h>

int createEventfd()
{
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        //nop
    }
    return evtfd;
}

#endif