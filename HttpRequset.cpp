#include "HttpRequset.h"
#include "./utils/Channel.h"
#include "./utils/Utils.h"
#include "./HttpMsg.h"
#include "FileData.h"
#include "FileHandler.h"

#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace WebServer;
using namespace std;

// HttpRequset::HttpRequset()
// :   _cSocket(C_Socket(-1)),
//     _loop(NULL)
// {

// }

HttpRequset::HttpRequset(C_Socket cSocket,EpollLoop *loop)
:   _cSocket(cSocket),
    _loop(loop),
    _connState(CONNECTED),
    _praseState(PRASE_START)
{
    // chan->setHolder(shared_from_this());
    // chan->setFd(_cSocket.getSocket());
    // chan->setReadHanedler(bind(&HttpRequset::readHandler, shared_from_this()));
    // chan->setWriteHanedler(bind(&HttpRequset::writeHandler, shared_from_this()));
    // chan->setConnHandler(bind(&HttpRequset::connHander, shared_from_this()));
    // chan->setSetEvents(EPOLLIN|EPOLLET);
}
void HttpRequset::doTest()
{
    cout << "test http requset" <<endl;
}

void HttpRequset::connHander()
{
    if(_connState == DISCONNECTING){
        closeHandler();
        return ;
    }
    if(*_setEventsPtr != 0)
    {
        ChannelPtr tmpChan = _chanPtr.lock();
        _loop->modEvent(tmpChan);
    }else {
        closeHandler();
    }
}

void HttpRequset::readHandler()
{
    string msg;
    //cout << "readhandle" << endl;
    bool zero = false;
    _cSocket.readnSocket(msg, zero);
    if(_connState == DISCONNECTING || _connState == DISCONNECTED){
        return ;
    }
    if(zero){
        _connState = DISCONNECTING;
        return ;
    }
    bool berror = false;
    bool ret = false;
    if(_praseState == PRASE_START)
    {
        ret = _reqMsg.parseRequsetLine(msg, berror);//解析请求行
        if(ret){
            _praseState = PRASE_URL_END;
        }
        else if(berror)
        {
            _connState = DISCONNECTING;
            _praseState = PRASE_ERROR;
        }
    }
    if(_praseState == PRASE_URL_END)
    {
        berror = false;
        ret = _reqMsg.parseHeanders(msg, berror); //解析请求头部
        if(ret){
            _praseState = PRASE_HEADERS_END; 
        }
        else if(berror)
        {
            _connState = DISCONNECTING;
            _praseState = PRASE_ERROR;
        }
    }
    if(_praseState == PRASE_HEADERS_END)
    {
        berror = false;
        ret = _reqMsg.parseContent(msg, berror); //解析请求内容
        if(ret){
            _praseState = PRASE_CONTENT_END; 
        }
        else if(berror)
        {
            _connState = DISCONNECTING;
            _praseState = PRASE_ERROR;
        }
    }
    if(_praseState = PRASE_CONTENT_END){
        cout << "+++++++++++++++++++++++++++" << endl;
        cout << msg << endl;
        cout << "+++++++++++++++++++++++++++" << endl;
        doRequset();
    }
    else if(!berror){
        *_setEventsPtr = EPOLLIN|EPOLLET;
    }
}

void HttpRequset::doRequset()
{
    if(_reqMsg._sUrl == "/favicon.ico") 
    {
        _connState = DISCONNECTING;
        return ;
    }
    string pageContent;
    cout << "-------------------------------------" << endl;
    cout << _reqMsg.toStr() << endl;
    cout << "-------------------------------------" << endl;
    if(readWebPage("/", pageContent))
        _rspMsg._sContent = pageContent;
    if(_reqMsg._sUrl == "/ls")
    {
        cout << "do ls......" << endl;
        FileReqMsgST fileMsg;
        fileMsg.sPath = "./data/";
        FileInfoListST vList;
        FileHandler::getFileList(fileMsg.sPath, vList);
        ostringstream content;
        content << "<table>";
        for(int i = 0; i < vList.size(); i++)
        {
            content << "<tr><td>" << vList[i].sFileName << "</td><td>" << vList[i].iFileType << "</td></tr>";
            //cout << "<tr><td>" << vList[i].sFileName << "</td><td>" << vList[i].iFileType << "</td></tr>" << endl; 
        }
        content << "</table>";
        _rspMsg._sContent += content.str();
    }
    cout << "-------------------------------------" << endl;
    cout << _rspMsg.toStr() << endl;
    cout << "-------------------------------------" << endl;
    
    *_setEventsPtr = EPOLLOUT|EPOLLET;
}


void HttpRequset::writeHandler()
{
    string msg = _rspMsg.toStr();
    _cSocket.writenSocket(msg);
    _connState = DISCONNECTING;
}

void HttpRequset::errorHandler()
{

}
void HttpRequset::closeHandler()
{
    ChannelPtr tmpChan = _chanPtr.lock();
    _loop->delEvent(tmpChan);
    _cSocket.closeSocket();
    _connState = DISCONNECTED;
}
