#include "HttpServer.h"
#include <stdio.h>

using namespace WebServer;

int main(){
    HttpServer *server = new HttpServer(10088);
    server->start();
    return 0;
}