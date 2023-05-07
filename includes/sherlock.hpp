#ifndef SHERLOCK_INCLUDED 
#define SHERLOCK_INCLUDED
// Sherlock is the built-in type safechecker.

#include <vector>
#include <string>

// This will register the index of invalid loops.
std::vector<int> invalid_loops(const std::string& src);
// Checks if the character is a brainfuck built-in command 
bool isBuiltinToken(const char& c);
int check_loops(const std::string& src);

#endif