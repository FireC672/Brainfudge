#include "util.hpp"
#include <string>
#include <cmath>
#include <cctype>

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