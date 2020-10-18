#ifndef C_SOCKET_H
#define C_SOCKET_H
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>


//using namespace std;

namespace WebServer{
    static const int BUFFSIZE = 1024;
    //static const int LISTENSIZE = 10;

    class C_Socket{
    private:
        
        int _fd;
        std::string _ip;
        sa_family_t _family;
        uint16_t _port;
        int _domain;
        int _sockType;
        int _protocol;
        //char _buff[BUFFSIZE];
        int _listenSize;
        bool _isClose;

    public:

        C_Socket();
        C_Socket(int fd);
        //C_Socket(int port);
        void setSocket(uint16_t fd){ _fd = fd; }
        void setFamily(sa_family_t fa){ _family = fa; } //协议族
        void setIp(std::string ip){ _ip = ip;}
        void setPort(int port){ _port = port; }
        int  getPort(){return _port;}
        void setDomain(int iDom){ _domain = iDom; } 
        void setSockType(int st){ _sockType = st; } 
        void setProtocol(int p){ _protocol = p; } 
        void setListenSize(int lss){ _listenSize = lss; }
        
        std::string getIp();
        int getSocket(){ return _fd; }

        bool createSocket();
        bool bindSocket();
        bool listenSocket();
        //bool connectSocket(char *ip,char *port);
        bool connectSocket(const std::string &ip, const int &port);
        bool acceptConn(C_Socket &newtSocke);
        void closeSocket();
        void shutDownWR();

        void setSocketNodelay();
        void setSoReuseAddr();
        //void setNonBlocking();

        ssize_t readSocket(std::string &msg);
        bool readnSocket(std::string &msg, bool &zero);
        bool writeSocket(std::string &msg);
        ssize_t writenSocket(std::string &msg);

    };

}

#endif