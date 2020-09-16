#include "C_Socket.h"
#include <cstring>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

using namespace WebServer;
using namespace std;

C_Socket::C_Socket()
:   _fd(-1),
    _family(AF_INET),
    _port(0),
    _domain(PF_INET),
    _sockType(SOCK_STREAM),
    _listenSize(10),
    _protocol(0),
    _isClose(false)
{
    // printf("init");
    // struct sockaddr_in addr;
    // addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
    // _ip = string(inet_ntoa(addr.sin_addr));
    //memset(_buff, 0, sizeof(_buff)*BUFFSIZE);
}

C_Socket::C_Socket(int fd)
:   _fd(fd),
    _family(AF_INET),
    _ip(""),
    _port(-1),
    _domain(PF_INET),
    _sockType(SOCK_STREAM),
    _listenSize(2048),
    _protocol(0),
    _isClose(false)   
{
    // struct sockaddr_in addr;
    // addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // _ip = string(inet_ntoa(addr.sin_addr));
}

// string C_Socket::getLocalIp()
// {
//     struct sockaddr_in addr;
//     cout << INADDR_ANY <<endl;
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
//     string ip = string(inet_ntoa(addr.sin_addr));
//     return ip;
// }
string C_Socket::getIp(){
    return _ip;
}

bool C_Socket::createSocket()
{
    _fd = socket(_domain, _sockType, _protocol);
    if(_fd == -1) return false;
    else return true;
}

bool C_Socket::bindSocket()
{
    if(_fd == -1 || _port == -1) return false;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = _family;
    //if(_ip == "") _ip = getLocalIp();
    if(_ip != "")
        addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    else 
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //cout << addr.sin_addr.s_addr << endl;
    addr.sin_port = htons(_port);
    
    int ret = bind(_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1) return false;
    else return true; 
}

bool C_Socket::listenSocket()
{
    int ret = listen(_fd, _listenSize);
    if(ret == -1) return false;
    else return true; 
}
void C_Socket::setSocketNodelay()
{
    int enable = 1;
    if(_fd == -1) return ;
    setsockopt(_fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
}
void C_Socket::setSoReuseAddr()
{
    int enable = 1;
    if(_fd == -1) return ;
    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&enable, sizeof(enable));
}

bool C_Socket::acceptConn(C_Socket &newtSocket)
{
    struct sockaddr_in addr;
    socklen_t len;
    int retFd = accept(_fd, (struct sockaddr*)&addr, &len);

    if(retFd == -1) return false;
    newtSocket.setSocket(retFd);
    newtSocket.setFamily(addr.sin_family);
    string ip(inet_ntoa(addr.sin_addr));
    newtSocket.setIp(ip);
    newtSocket.setPort(ntohs(addr.sin_port));
    //newtSocket.setSocketNodelay();
    return true;

}

void C_Socket::closeSocket()
{
    _isClose = true;
    close(_fd);
}

void C_Socket::shutDownWR()
{
    shutdown(_fd, SHUT_WR);
}

ssize_t C_Socket::readSocket(string &msg)
{
    char buff[BUFFSIZE];
    ssize_t readNum = 0;
    readNum = read(_fd, buff, BUFFSIZE);
    if(readNum > 0){
        msg.append(buff, readNum);
    }
    return readNum;
}
    

bool C_Socket::readnSocket(string &msg, bool &zero)
{
    ssize_t readNum = 0;
    char buff[BUFFSIZE];
    zero = false;
    while(true)
    {
        //cout << " read " << endl;
        readNum = read(_fd, buff, BUFFSIZE);
        //cout << readNum << string(buff, readNum) << endl;
        if(readNum < 0)
        {
            //cout<< "read1" <<endl;
            if(errno == EINTR){
                continue;
            }
            else if(errno == EAGAIN){
                //cout<< "read2" <<endl;
                return true;
            }else {
                //cout<< "read3" <<endl;
                return false;
            }
        }
        else if(readNum > 0)
        {
            //cout<< "read4" <<endl;
            msg.append(buff, readNum);
        }
        else if(readNum == 0) 
        {
            zero = true;
            return true;
        }
    }
    return false;
}

bool C_Socket::writeSocket(string &msg)
{
    //string::iterator it=msg
    if(msg.empty()) return true;
    cout << msg << endl;
    ssize_t writeNum = write(_fd, msg.c_str(), msg.size());
    if(writeNum == -1) return false;
    return true;
}

ssize_t C_Socket::writenSocket(string &sbuff)
{
    size_t nleft = sbuff.size();
    ssize_t nwritten = 0;
    ssize_t writeSum = 0;
    const char *ptr = sbuff.c_str();
    while (nleft > 0)
    {
        if ((nwritten = write(_fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0)
            {
                if (errno == EINTR)
                {
                    nwritten = 0;
                    continue;
                }
                else if (errno == EAGAIN)
                    break;
                else
                    return -1;
            }
        }
        writeSum += nwritten;
        nleft -= nwritten;
        ptr += nwritten;
    }
    if (writeSum == static_cast<int>(sbuff.size()))
        sbuff.clear();
    else
        sbuff = sbuff.substr(writeSum);
    return writeSum;
}