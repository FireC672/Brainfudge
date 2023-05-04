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

// B_ASSERT TOOLS 
#define WARNING_LEVEL 1 
#define ERROR_LEVEL 2 
#define FATAL_ERROR_LEVEL 3
#define RUNTIME_ERROR_LEVEL 4

#include <string>
typedef unsigned char byte_t;
// This is reserved for my own functions.
// Special function
std::string str_c(char* chbuff, size_t csize);
// String to int.
int str_int(const std::string& str);
// Unsigned integer power func.
uint32_t upowi(uint32_t b, uint32_t n);
// String to unsigned integer.
uint32_t str_uint(const std::string& str);
// Removes backslashes
std::string remove_slash(std::string& v);
// Reverses string.
std::string revstr(std::string& s);

// _bassert => Brainfuck assert.
void __bassert__(bool e, int error_lvl, const std::string& msg);

#endif