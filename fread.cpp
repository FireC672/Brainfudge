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

std::stack<int> invalid_loops(const std::string& src){
    std::stack<int> state; 
    std::stack<int> state2;
    for(int i = 0; i < src.size(); i++){
          if(src[i]=='[')state.push(i);
          if(src[i]==']' && !state.empty())state.pop();
          if(src[i]==']' && state.empty())state2.push(i);
    }
    // Merge stacks 
    std::stack<int> finalStack; 
    for(int i = 0; i < state.size(); i++){
        finalStack.push(state.top());
        state.pop();
    }
    for(int i = state.size(); i < state2.size()+state.size(); i++){
        finalStack.push(state2.top());
        state2.pop();
    }
    return finalStack;
}