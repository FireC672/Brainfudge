#include "../includes/sherlock.hpp"

#include <vector>
#include <string>

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

int check_loops(const std::string& src){
    int depth=0;
    for(int i = 0; i < src.size(); i++){
        if(src[i]=='[')depth++; 
        if(src[i]==']')depth--;
    }
    // The point: if the func returns zero, then all the loops are valid ones.
    return depth;
}
