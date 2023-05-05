#include "../includes/util.hpp"
#include <string>
#include <cmath>
#include <cctype>
#include <iostream>
#include <vector>

std::string str_c(char* chbuff, size_t csize){
    std::string b; 
    for(int i = 0; i < csize; i++){
        b.push_back(chbuff[i]);
    }
    return b;
}

int str_int(const std::string& str){
    int tot = 0;
    int k = str.size()-1;
    for(int i = 0; i < str.size(); i++){
       if(!isdigit(str[i]))return tot; 
       tot += static_cast<int>((str[i]-'0')*pow(10,k));
       k--;
    }
    return tot;
}


uint32_t upowi(uint32_t b, uint32_t n){
    uint32_t t = 1;
    for(int i = 0; i < n; i++)t*=b; 
    return t;
}

uint32_t str_uint(const std::string& str){
    if(str.empty())return 0u;
    std::string dig;
    for(int j = 0; j < str.size();j++){
        if(str[j] >= '0' && str[j] <= '9')dig.push_back(str[j]);
    }
    if(dig.empty())return 0u;
    
    int i = dig.size()-1;
    unsigned int tot = 0;
    for(int j = 0; j < dig.size();j++){
       tot += (dig[j]-'0') * (upowi(10,i));
       i--;
    }
    return tot;
}

std::string remove_slash(std::string& v){
    std::string b; 
    for(auto& k : v){
        if(k == '\\')continue; 
        b.push_back(k);
    }
    return b;
}

std::string revstr(std::string& s){
    std::string ou = s;
    int j = ou.size()-1;
    for(int i = 0; i < s.size(); i++){
        ou[j] = s[i];
        j--;
    }
    return ou;
}

void __bassert__(bool e, int error_lvl, const std::string& msg){

    if(e)return;

    switch (error_lvl)
    {
        case WARNING_LEVEL:
            std::cerr << YELLOW_CODE << BOLD_TEXT
                      << "warning: " << CLEAR_FLG;      
            break;
        case ERROR_LEVEL:
            std::cerr << RED_CODE << BOLD_TEXT
                      << "error: " << CLEAR_FLG;       
            break;
        case FATAL_ERROR_LEVEL:
            std::cerr << RED_CODE << BOLD_TEXT
                      << "fatal error: " << CLEAR_FLG;   
            break;    
        case RUNTIME_ERROR_LEVEL:
            std::cerr << RED_CODE << BOLD_TEXT 
                      << "runtime error: "<< CLEAR_FLG;
            break;
        default:
            std::cerr << YELLOW_CODE << BOLD_TEXT 
                      << "undefined exception: " << CLEAR_FLG;
            break;
             
    }

    std::cerr << msg;
    exit(1);
}