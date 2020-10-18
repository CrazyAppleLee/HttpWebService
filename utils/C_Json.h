#ifndef C_JSON_H
#define C_JSON_H

#include <string>
#include <map>
#include <vector>
namespace WebServer{

    class C_Json{
        private:        

        public:
            static bool str2map(const std::string &sJson, std::map<std::string,std::string> &mValue);
            static bool str2vmap(const std::string &sJson, std::vector<std::map<std::string,std::string>> &vValueMap);
            static bool toValueString(std::string &sStr);
            static std::vector<std::string> splitJsonContent(const std::string &sStr);
            static std::vector<std::string> splitJsonVector(const std::string &sStr);
            static std::string addTR(const std::string &sStr);//转义符\\ \"
            static std::string delTR(const std::string &sStr);
    };
    
}

#endif 