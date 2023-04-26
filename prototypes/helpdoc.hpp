#ifndef __HELP_DOC_INCLUDED 
#define __HELP_DOC_INCLUDED 
#include <string>
std::string* inithelp();

// Initialize syntax help.
// by levels
std::string* initsynhelp(const int& level);
#endif