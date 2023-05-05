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

int check_loops(const std::string& src){
    int loopcheck=0;
    for(int i = 0; i < src.size(); i++){
        if(src[i]=='[')loopcheck++; 
        if(src[i]==']')loopcheck--;
    }
    // The point: if the func returns zero, then all the loops are valid ones.
    return loopcheck;
}

std::vector<int> invalid_loops(const std::string& src){
    std::vector<int> loopstates;
    for(int i = 0; i < src.size(); i++){
          if(src[i]=='[')loopstates.push_back(i);
          if(src[i]==']' && loopstates.size() > 0)loopstates.pop_back();
          //if(src[i]==']' && loopstates.size() == 0)loopstates.push_back(i);
    }
    return loopstates;
}

// Useful for finding conflicts
bool isBuiltinToken(const char& c){
    return (c == '>' || c == '<' || c == '+' || c == '-' || c == '[' || c == ']'
           || c == '.' || c == ',' || c == '#' || c == '!');
}
unsigned int memoryDemand(const std::string& src){
    unsigned int maxDemand = 1;
    unsigned int currentDemand = 0;
    for(auto& token : src){
        if(token == '>'){
           currentDemand++;
           if(currentDemand > maxDemand)maxDemand = currentDemand;
        }
    }
    return maxDemand;
}