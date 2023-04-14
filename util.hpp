#ifndef __UTIL_HPP_INCLUDED 
#define __UTIL_HPP_INCLUDED 

// Color codes 
// TODO: Support 'Windows' codes
#define RED_CODE "\033[31m"
#define GREEN_CODE "\033[32m"
#define YELLOW_CODE "\033[33m"
#define BLUE_CODE "\033[34m"
#define PURPLE_CODE "\033[35m"
#define GREY_CODE "\033[30m"
#define CYAN_CODE "\033[36m"
#define BOLD_TEXT "\033[1m"
#define CLEAR_FLG "\033[0m"


#include <string>
// This is reserved for my own functions.
// Special function
std::string str_c(char* chbuff, size_t csize);
// String to int.
int str_int(const std::string& str);
#endif