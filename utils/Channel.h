#ifndef CHANNEL_H
#define CHANNEL_H

#include "C_SQueue.h"
#include "C_Socket.h"
#include "C_Epoll.h"
#include <functional>
#include <memory>

namespace WebServer{
    class HttpRequset;
    class C_Epoll;
    class Channel{
    private:
        typedef std::function<void()> CallBack;
        CallBack _handler;
        CallBack _readHandler;
        CallBack _writeHandler;
        CallBack _errorHandler;
        CallBack _connHandler;

        std::shared_ptr<HttpRequset> _httpRequset;
        __uint32_t _setEvents; //设置监听的事件
        __uint32_t _retEvents; //触发的事件
        //C_Socket _cSocket; 
        int _fd;
        bool _doHandleEvent;
        
    public:
        Channel();
        Channel(std::shared_ptr<HttpRequset> requset, CallBack handler);
        ~Channel(){
            //cout << "Channel end fd " << _fd << endl;
        }
        void handleEvent();
        void handleRead()
        {
            if(_readHandler){
                _readHandler();
            }
        }
        void handleConn()
        {
            if(_connHandler){
                _connHandler();
            }
        }
        void handleWrite()
        {
            if(_writeHandler){
                _writeHandler();
            }
        }
        void handleError()
        {
            // if(errorHandler){
            //     _errorHandler();
            // }
        }
        void handle()
        {
            if(_handler){
                _handler();
            }else if(_doHandleEvent){
                handleEvent();
            }
        }
        void setFd(int fd) { _fd = fd; }

        void setHandler(CallBack cb){ _handler = cb; }

        void setErrorHandler(CallBack cb){ _errorHandler = cb; }
    
        void setReadhanedler(CallBack cb){ _readHandler = cb; }

        void setWritehanedler(CallBack cb){ _writeHandler = cb; }

        void setConnHandler(CallBack cb){ _connHandler = cb; }

        void setRetEvents(__uint32_t ev){ _retEvents = ev; }

        void setSetEvents(__uint32_t ev){ _setEvents = ev; }

        void setDoHandleEvent(bool t){ _doHandleEvent = t; }

        __uint32_t getSetEvents(){ return _setEvents; } 

        __uint32_t getRetEvents(){ return _retEvents; }

        int getFd() { return _fd; }

    };

    typedef std::shared_ptr<Channel> ChannelPtr;
    typedef C_SQueue<ChannelPtr> ChannelsQueue;
    typedef std::shared_ptr<ChannelsQueue> ChannelsQueuePtr;


}
#endif