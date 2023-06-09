/* fread.hpp means file read 
   so this file will contain stub functions 
   for file reading
*/
#include <string> 

#ifndef __FREAD_HPP_INCLUDED
#define __FREAD_HPP_INCLUDED

// extract_syntax() will extract the valid syntax.
// 'bIgnoreComments' will ignore comments in the code (all characters followed by '#' will be treated as comment even if they are valid syntax)
// 'bIgnoreHalts' will ignore halts '!'
std::string extract_syntax(const std::string& src, bool bIgnoreComments=false, bool bIgnoreHalts=false, char snapshot_token='%', bool bSaveSnapshot=false);
// This function will check, if all the loops in the program have endings & beginnings.

// will calculate how much the program needs memory. (Excluding loops)
unsigned int memoryDemand(const std::string& src);

#endif