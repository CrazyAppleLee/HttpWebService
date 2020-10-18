#include "FileHandler.h"
#include "FileData.h"

#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;
using namespace WebServer;

bool FileHandler::getFileList(const string &path, FileInfoListST &vFileInfos)
{
    //FileInfoList vFileInfos;
    string sPath = path;
    if(sPath[sPath.size()-1] != '/') sPath += "/";
    DIR *dir = NULL;
    struct dirent *entry;
    struct stat stInfo;
    if((dir = opendir(sPath.c_str()))==NULL)  
    {  
        //printf("opendir failed!");  
        return false;  
    }
	else  
    {  
        while(entry=readdir(dir))  
        {  
            //i++;
            string sFileName(entry->d_name);
            FileType fileType = TYPE_FILE;
            // if(fileName == "."||fileName == "..")
            // {
            //     continue;
            // }
            FileInfo stFileInfo;
            stFileInfo.sFileName = sFileName;
            string sFilePath = sPath + sFileName;
            if(stat(sFilePath.c_str(), &stInfo) == -1)
            {
                continue;
            }
            if(S_ISREG(stInfo.st_mode)) fileType = TYPE_FILE;
            else if(S_ISDIR(stInfo.st_mode)) fileType = TYPE_DIR;
            stFileInfo.iFileType = fileType;
            vFileInfos.push_back(stFileInfo);
            //cout <<"fileName: " << fileName <<endl; 

        }
        closedir(dir);
     }
     return true;
}