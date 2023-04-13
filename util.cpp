#include "util.hpp"
#include <string>

std::string str_c(char* chbuff, size_t csize){
    std::string b; 
    for(int i = 0; i < csize; i++){
        b.push_back(chbuff[i]);
    }
    return b;
}