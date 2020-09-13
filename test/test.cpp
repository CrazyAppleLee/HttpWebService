#include "../utils/C_Thread.h"
#include "../utils/C_MutexLock.h"
#include "../utils/C_Socket.h"
#include "../utils/C_SQueue.h"
#include "../Channel.h"
#include "../HttpRequset.h"
#include "../HandleThread.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <sstream>
#include <functional>

using namespace std;
using namespace WebServer;

void testSocket()
{
    int port = 10068;
    printf("new\n");
    C_Socket cSocket(port);
    printf("setPort\n");
    cSocket.setPort(port);
    printf("createSocket\n");
    if(!cSocket.createSocket()){
        cout << "createSocket error" << endl;
    }
    cSocket.setSoReuseAddr();
    //cout<< cSocket.getLocalIp()<<endl;
    printf("bindSocket\n");
    if(!cSocket.bindSocket()){
        cout << "bindSocket error" << endl;
    }
    printf("listenSocket\n");
    if(!cSocket.listenSocket()){
        cout << "listenSocket error" << endl;
    }
    C_Socket newSocket;
    int count=0;
    while(true){
        cSocket.acceptConn(newSocket);
        //newSocket.setSocketNodelay();
        string strRead;
        printf("acceptedConn\n");
        if(newSocket.readSocket(strRead)==-1)
        {
            continue;
            newSocket.closeSocket();
        }
        cout << strRead <<endl;
        
        ostringstream rsp;
        rsp << "HTTP/1.1 200 OK\r\n";
        //rsp +=          "Content-Type: text/plain\r\n";
        rsp << "\r\n";
        rsp << "<html>";
        rsp << "index page " << count;
        rsp << "</html>";
        string str(rsp.str());
        if(str.find("/favicon.ico") != -1) 
        {
            newSocket.closeSocket();
            continue;
        }
        newSocket.writeSocket(str);
        newSocket.closeSocket();
        //newSocket.shutDownWR();
        count ++;
        cout << "count " << count << " ip = "<< newSocket.getIp() <<endl << endl;
    }

}

void testQueue()
{
    C_SQueue<int> qu;
    int i=10;
    qu.push(4);
    qu.push(3);
    //int i = 0;
    qu.pop(i);
    cout << i << endl;
    qu.pop(i);
    cout << i << endl;
}
void fun()
    {
        cout << "Test Channel" << endl;
    }
void testChannel()
{
    
    shared_ptr<HttpRequset> requset = make_shared<HttpRequset>();
    Channel chan(requset, bind(&HttpRequset::doTest, requset));
    //chan.setHandler(fun);
    //chan.handle();
    cout<< "test start" <<endl;
    std::shared_ptr<C_SQueue<Channel>> chansQ = make_shared<C_SQueue<Channel>>();
    chansQ->push(chan);
    cout<< "chansQ->push(chan);" <<endl;
    HandleThread *handleThread = new HandleThread();
    cout<< "new HandleThread();" <<endl;
    handleThread->setQueuePtr(chansQ);
    handleThread->run();


}
int main(){
    //testSocket();
    //testQueue();
    testChannel();
    return 0;
}