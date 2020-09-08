#include "Epoll.h"
#include "utils/Common.h"

Epoll::Epoll()
:   _epollFd(createEpollFd())
{

}
Epoll::~Epoll()
{
    close(_epollFd);
}

