#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <memory>

namespace WebServer{
    class HttpRequset;
    class Channel{
    private:
        std::function<void()> _handler;
        std::shared_ptr<HttpRequset> _httpRequset;
    public:
        Channel(){}
        Channel(std::shared_ptr<HttpRequset> requset, std::function<void()> handler)
        :   _httpRequset(requset),
            _handler(handler)
        {

        }

        void setHandler(std::function<void()> fun){
            _handler = fun;
        }

        void handle(){
            if(_handler){
                _handler();
            }
        }
    };


}
#endif