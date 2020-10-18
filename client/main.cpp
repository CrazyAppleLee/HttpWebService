#include "Client.h"

#include <string>
//#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace ClientSpace;

int main(int argc, char *argv[])
{
    if(argc < 4)
    {
        cout << "please input<username, serverip, serverport>." << endl;
        return 0;
    }
    string sUserName(argv[1]), sServerIp(argv[2]);
    int iServerPort = atoi(argv[3]);
    cout << "UserName = " << sUserName << "|ServerIp = " << sServerIp << "|ServerPort = " << iServerPort << endl;
    return 0;
}