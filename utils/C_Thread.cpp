#include "C_Thread.h"
#include<pthread.h>
#include <functional>
#include <iostream>

using namespace std;
using namespace WebServer;


static void *runThread(void* args)
{
    cout << "runThread start ...." << endl;
    C_Thread *cTread = (C_Thread*)args;
    cTread->run();
    return NULL;
}

C_Thread::C_Thread()
:   _bStarted(false),
    _bJoin(false),
    _pId(-1),
    _runFun(NULL)
{
    
}
C_Thread::C_Thread(Function runFun)
:   _bStarted(false),
    _bJoin(false),
    _pId(-1)
{
    _runFun = runFun;
}

bool C_Thread::start()
{
    cout << "Thread start ...." << _bStarted << endl;
    if(!_bStarted)
    {
        cout << "_bStarted false ...." << endl;
        _bStarted = true;
        if(pthread_create(&_pId, NULL, &runThread, this) != 0)
        {
            cout << "Thread start error" << endl;
            _bStarted = false;
            return false;
        }
    }
    return true;
}
bool C_Thread::join(){
    if(!_bJoin && _bStarted)
    {
        _bJoin = true;
        if(pthread_join(_pId, NULL) != 0){
            _bJoin = false;
            return false;
        }
        return true;
    }
    return false;
}

void C_Thread::run(){
    if(_runFun)
        _runFun();
}
