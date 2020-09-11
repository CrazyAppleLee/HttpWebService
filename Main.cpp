#include "utils/C_Socket.h"
//#include "utils/C_MutexLock.h"
#include <stdio.h>

using namespace WebServer;

int main(){

    int port = 10088;
    printf("new\n");
    C_Socket cSocket(port);
    printf("setPort\n");
    cSocket->setPort(port);
    printf("createSocket\n");
    cSocket->createSocket();
    printf("bindSocket\n");
    cSocket->bindSocket();
    printf("listenSocket\n");
    cSocket->listenSocket();
    C_Socket newSocket;
    cSocket->acceptConn(newSocket);
    sttring strRead;
    newSocket.readSocket(strRead);
    cout << strRead <<endl;
    return 0;
}