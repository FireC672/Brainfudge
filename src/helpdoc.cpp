#include "../prototypes/helpdoc.hpp"
#include <string>

std::string* inithelp(){
    std::string* hlp = new std::string("");
    *hlp = 
    "--ignore-comments:          Ignores comments \'#\' in the source file."
    "\n--ignore-halts:           Ignores \'!\' known as halts."
    "\n--unsignal-halt:          Treats a halt as program ending without signaling."
    "\n--prg-settings:           Displays the setup settings in the program (eg: Memory allocated)."
    "\n--count-instructions:     Counts the instructions that have been executed."
    "\n--license | -l | -lc:     Displays the GNU General public license."
    "\n\n(Syntax-Highlighting)\n\n"
    "--syntax-highlight:         Switchs to the syntax highlighter."
    "\n--disable-comments:       Hides the comment."
    "\n--disable-commenthash:    Hides the \'#\' but still shows the comment."
    "\n--line-number:            Shows the current line.\n"
    "\n--precision-halt:         Shows the exact place where the halt happend.\n";
    return hlp;
}