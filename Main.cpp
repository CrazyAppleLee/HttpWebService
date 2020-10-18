//#include "HttpServer.h"
#include "MyServer.h"
#include "EpollLoop.h"
#include "LoopThreadPool.h"
#include <stdio.h>

using namespace WebServer;
using namespace std;

int main(){
    //HttpServer *server = new HttpServer(10088);
    //server->start();
    EpollLoop *loop = new EpollLoop();
    LoopThreadPool *LoopPool = new LoopThreadPool(loop);
    cout << loop << " "<< LoopPool << endl;
    MyServer *server = new MyServer(loop, LoopPool, 10098);
    server->start();
    return 0;
}