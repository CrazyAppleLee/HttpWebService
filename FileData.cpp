#include "FileData.h"
#include "./utils/C_Json.h"
#include "./utils/Utils.h"

#include <sstream>
#include <string>
#include <map>
using namespace std;
using namespace WebServer;

string FileInfo::toJsonStr()
{
    ostringstream ss;
    ss << "{";
    ss << "\"sFileName\":\"" << sFileName << "\",";
    ss << "\"sPath\":\"" << sPath << "\",";
    ss << "\"iFileType\":\"" << iFileType << "\",";
    ss << "\"iSize\":\"" << iSize << "\"";
    ss << "}";
    return ss.str();
}
bool FileInfo::readFromJson(const string &sStr)
{
    map<string, string> mValue;
    if(!C_Json::str2map(sStr, mValue))
    {
        return false;
    }
    try{
        sFileName = mValue["sFileName"];
        sPath = mValue["sPath"];
        int t;
        if(str2int(mValue["iFileType"], t)){
            iFileType = FileType(t);
        }
        else {
            return false;
        }
        if(str2int(mValue["iSize"], t)){
            iSize = t;
        }
        else {
            return false;
        }
        return true;
    }catch(exception e){
        return false;
    }
}


string FileInfoList::toJsonStr()
{
    ostringstream ss;
    ss << "[";
    if(vValue.empty()){
        ss << "}]"; 
        return ss.str();
    }
    ss << vValue[0].toJsonStr();
    for(int i = 1; i < vValue.size(); i++)
    {
        ss << "," << vValue[0].toJsonStr();
    }
    ss << "]";
    return ss.str();
}
bool FileInfoList::readFromJson(const string &sStr)
{
    vector<string> vJson = C_Json::splitJsonVector(sStr);
    for(int i = 0; i < vJson.size(); i ++)
    {
        FileInfoST stFileInfo;
        if(stFileInfo.readFromJson(vJson[i]))
        {
            vValue.emplace_back(move(stFileInfo));
        }
        else {
            return false;
        }
    }
    return true;
}