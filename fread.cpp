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

int check_loops(const std::string& src){
    int loopcheck=0;
    for(int i = 0; i < src.size(); i++){
        if(src[i]=='[')loopcheck++; 
        if(src[i]==']')loopcheck--;
    }
    // The point: if the func returns zero, then all the loops are valid ones.
    return loopcheck;
}
std::string str_c(char* chbuff, size_t csize){
    std::string b; 
    for(int i = 0; i < csize; i++){
        b.push_back(chbuff[i]);
    }
    return b;
}