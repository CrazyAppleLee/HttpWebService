#include "../utils/C_Thread.h"
#include "../utils/C_MutexLock.h"
#include "../utils/C_Socket.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace WebServer;

int main(){

    int port = 10088;
    printf("new\n");
    C_Socket cSocket(port);
    printf("setPort\n");
    cSocket.setPort(port);
    printf("createSocket\n");
    cSocket.createSocket();
    cout<< cSocket.getLocalIp()<<endl;
    printf("bindSocket\n");
    cSocket.bindSocket();
    printf("listenSocket\n");
    cSocket.listenSocket();
    C_Socket newSocket;
    cSocket.acceptConn(newSocket);
    string strRead;
    printf("acceptedConn\n");
    newSocket.readSocket(strRead);
    cout << strRead <<endl;

    return 0;
}