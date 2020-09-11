#include "C_Thread.h"
#include<pthread.h>
#include <functional>

using namespace std;
using namespace WebServer;


static void *runThread(void* args)
{
    C_Thread *cTread=(C_Thread*)args;
    cTread->run();
    return NULL;
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
    if(!_bStarted)
    {
        _bStarted=true;
        if(pthread_create(&_pId, NULL, &runThread, this) != 0)
        {
            _bStarted = false;
            return false;
        }
    }
    return true;
}
bool C_Thread::join(){
    if(!_bJoin&&_bStarted)
    {
        _bJoin=true;
        if(pthread_join(_pId, NULL) != 0){
            _bJoin =false;
            return false;
        }
        return true;
    }
    return false;
}

void C_Thread::run(){
    _runFun();
}
