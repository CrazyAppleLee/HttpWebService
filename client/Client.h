#ifndef CLIENT_H
#define CLIENT_H

#include "../utils/C_Socket.h"
#include "../FileData.h"
#include "../FileHandler.h"
#include <string>
namespace ClientSpace{
    
    class Client{
    private:
        std::string _sServerIP;
        int _iServerPort;
        std::string _sCurrentPath;
        std::string _sUserName;
        WebServer::C_Socket _cSocket;

    public:
        Client(const std::string &sUserName, const std::string &sServerIP, const int &iServerPort);
        void start();
        WebServer::FileRspMsg getFileList(std::string &sPath);
    };
}

#endif 