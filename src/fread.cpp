#include "../includes/fread.hpp"
#include <string>
#include <vector>

std::string extract_syntax(const std::string& src, bool bIgnoreComments, bool bIgnoreHalts, char snapshot_token, bool bSaveSnapshot){
    std::string extracted;
    for(int i = 0; i < src.size(); i++){
        if(src[i] == '#' && !bIgnoreComments){
            while(src[i]!='\n' && i < src.size())i++;
        }

        if(src[i] == '!' && !bIgnoreHalts){
            // This will happen at runtime.
            extracted.push_back(src[i]);
        }

        if(src[i]=='>' || src[i]=='<' ||
           src[i]=='+' || src[i]=='-' ||
           src[i]=='[' || src[i]==']' ||
           src[i]=='.' || src[i]==',' || (src[i] == snapshot_token && bSaveSnapshot))extracted.push_back(src[i]);
    }
    return extracted;
}

unsigned int memoryDemand(const std::string& src){
    unsigned int maxDemand = 1;
    unsigned int currentDemand = 0;
    for(auto& token : src){
        if(token == '>'){
           currentDemand++;
           if(currentDemand > maxDemand)maxDemand = currentDemand;
        }

        if(token == '<')currentDemand--;
    }
    return maxDemand+1;
}