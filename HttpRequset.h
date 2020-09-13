#ifndef HTTPREQUSET_H
#define HTTPREQUSET_H

#include "./utils/C_Socket.h"
#include <string>
#include <memory>

namespace WebServer{
    class HttpRequset: public std::enable_shared_from_this<HttpRequset>{
    private:
        C_Socket _cSocket;
        std::string _reqMsg;
        std::string _rspMsg;
    public:
        HttpRequset(){}
        void readHandler();
        void doRequset();
        void writeHandler();
        void doTest();
    };
}

#endif