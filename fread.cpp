#include "fread.hpp"
#include <string>

std::string extract_syntax(const std::string& src, bool bIgnoreComments, bool bIgnoreHalts){
    std::string extracted; 
    for(int i = 0; i < src.size(); i++){
        if(src[i] == '#' && !bIgnoreComments){
            while(src[i]!='\n' && i < src.size())i++;
        }

        if(src[i] == '!' && !bIgnoreHalts){
            // This will happen at runtime.
            extracted.push_back(src[i]);
            break;
        }

        if(src[i]=='>' || src[i]=='<' ||
           src[i]=='+' || src[i]=='-' ||
           src[i]=='[' || src[i]==']' ||
           src[i]=='.' || src[i]==',')extracted.push_back(src[i]);
    }
    return extracted;
}