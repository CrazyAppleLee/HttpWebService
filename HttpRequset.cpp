#include "HttpRequset.h"
#include "./utils/Channel.h"

#include <iostream>
#include <sstream>

using namespace WebServer;
using namespace std;

HttpRequset::HttpRequset()
:   _cSocket(C_Socket(-1)),
    _reqMsg(""),
    _rspMsg("")
{

}

HttpRequset::HttpRequset(C_Socket cSocket)
:   _cSocket(cSocket),
    _reqMsg(""),
    _rspMsg("")
{

}

void HttpRequset::doTest(){
    cout << "test http requset" <<endl;
}

void HttpRequset::readHandler()
{
    
}

void HttpRequset::doRequset()
{
    ostringstream str;
    static int count = 0;
    str << "HTTP/1.1 200 OK\r\n";
    //rsp +=          "Content-Type: text/plain\r\n";
    str << "\r\n";
    str << "<html>";
    str << "index page " << count;
    count ++;
    str << "</html>";
    _rspMsg = string(str.str());
}

void HttpRequset::writeHandler()
{

}