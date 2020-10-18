#include "C_Json.h"
#include "Utils.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;
using namespace WebServer;

bool C_Json::str2map(const string &sJson, map<string, string> &mValue)
{
    string sTmpStr = trimLeftandRight(sJson, "\n\r{ ", " }\n\r");
    vector<string> vStr = splitJsonContent(sTmpStr);
    vector<string> vTmp; 
    string sKey, sValue;
    for(int i = 0; i < vStr.size(); i++)
    {
        if(vStr[i].size() == 0)
        {
            continue;
        }
        vTmp = split1st(vStr[i], ":");
        if(vTmp.size() !=2 ) 
        {
            return false;
        }
        sKey = vTmp[0];
        if(!toValueString(sKey))
        {
            return false;
        }
        sValue = vTmp[1];
        if(!toValueString(sValue))
        {
            return false;
        }
        mValue[sKey] = sValue;
    }
    return true;

}

bool C_Json::str2vmap(const string &sJson, vector<map<string, string>> &vValueMap)
{
    vector<string> vString = splitJsonVector(sJson);
    for(int i = 0; i < vString.size(); i++)
    {
        map<string, string> mValue;
        if(str2map(vString[i], mValue)){
            vValueMap.emplace_back(move(mValue));
        }
        else {
            return false;
        }
    }
    return true;
}
bool C_Json::toValueString(string &sStr)
{
    sStr = trimLeftandRight(sStr, " \n\r\t" , " \n\r\t");
    if(sStr.size() == 0)
    {
        return false;
    }
    bool bCut = false;
    if(sStr[0] == '\"' && sStr[sStr.size()-1] == '\"')
    {
        bCut = true;
    }
    else if(sStr[0] == '\'' && sStr[sStr.size()-1] == '\'')
    {
        bCut = true;
    }
    if(bCut)
    {
        sStr = sStr.substr(1, sStr.size()-2);
    }
    return true;
}
vector<string> C_Json::splitJsonContent(const string &sStr)
{
    bool bHasSp = false;
    int p = 0;
    bool bInword =false;
    int i = 0;
    vector<string> vString;
    while(i < sStr.size()){
        if(bInword)
        {
            if(sStr[i] == '\"' && i > 0 && sStr[i-1] != '\\')
            {
                bInword = false;
            }
        }
        else if(!bInword){
            if(sStr[i] == '\"')
            {
                bInword = true;
            }
            else if(sStr[i] == ',' && bHasSp)
            {
                vString.emplace_back(sStr.substr(p, i - p));
                p = i + 1;
                bHasSp =false;
            }
            else if(sStr[i] == ':')
            {
                bHasSp = true;
            }
        }
        i++;
    }
    if(p != i){
        vString.emplace_back(sStr.substr(p, sStr.size()-p));
    }
    return vString;
}
vector<string> C_Json::splitJsonVector(const std::string &sStr)
{
    vector<string> vString;
    int num = 0; //大括号。
    int i = sStr.find_first_of('[') + 1;
    int p = i;
    int end = sStr.find_first_of(']');
    bool bInword = false;
    while(i < end)
    {
        if(bInword)
        {
            if(sStr[i] == '\"' && i > 0 && sStr[i-1] != '\\')
            {
                bInword = false;
            }
        }
        else if(!bInword){
            if(sStr[i] == '\"')
            {
                bInword = true;
            }
            else if(num == 0 && sStr[i] == ','){
                vString.emplace_back(sStr.substr(p, i - p));
                p = i+1;
            }
            if(sStr[i] == '{') num ++;
            else if(sStr[i] == '}') num --;
        }
        i++;
    }
    if(p != i){
        vString.emplace_back(sStr.substr(p, end-p));
    }
    return vString;

}
string C_Json::addTR(const string &sStr)
{
    ostringstream ss;
    int i = 0;
    while(i < sStr.size())
    {
        if(sStr[i] == '\"' || sStr[i] == '\\')
        {
            ss << '\\';
        }
        ss << sStr[i];
        i++;
    }
    return ss.str();
}
string C_Json::delTR(const string &sStr)
{
        ostringstream ss;
    int i = 0;
    //bool bT = true;
    while(i < sStr.size())
    {
        if(sStr[i] == '\"' || sStr[i] == '\\')
        {
            if(i+1 < sStr.size())
            {
                i++;
            }
            ss << sStr[i];
        }
        else 
        {
            ss << sStr[i];
        }

        i++;
    }
    return ss.str();
}
