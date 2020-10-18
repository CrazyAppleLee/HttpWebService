#include "Client.h"
#include "../FileData.h"
#include "../FileHandler.h"
#include "../utils/Utils.h"

#include <string>
#include <vector>

using namespace std;
using namespace WebServer;
using namespace ClientSpace;

Client::Client(const string &sUserName, const string &sServerIP, const int &iServerPort)
:   _sUserName(sUserName),
    _sServerIP(sServerIP),
    _iServerPort(iServerPort),
    _sCurrentPath("/")
{
    cout << "Client init" << endl;
}
void Client::start()
{
    string sCmd;
    vector<string> vCmds;
    while(true)
    {
        cout << "[" << _sUserName << _sCurrentPath << "]" << ">" << endl;
        getline(cin, sCmd);
        vCmds = split(sCmd, " ");
        if(vCmd.empty())
        {
            cout << "empty cmd" <<endl;
            continue;
        }
        if(vCmd[0] == "ls")
        {
            
        }
    }
}