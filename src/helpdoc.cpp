#include "../includes/helpdoc.hpp"
#include <string>

std::string* inithelp(){
    std::string* hlp = new std::string("");
    *hlp = 
    "--ignore-comments:        Ignores comments \'#\' in the source file."
    "\n--ignore-halts:           Ignores \'!\' known as halts."
    "\n--unsignal-halt:          Treats a halt as program ending without signaling."
    "\n--prg-settings:           Displays the setup settings in the program (eg: Memory allocated)."
    "\n--count-instructions:     Counts the instructions that have been executed."
    "\n--license | -l | -lc:     Displays the GNU General public license."
    "\n\n(Syntax-Highlighting)\n\n"
    "--syntax-highlight:       Switchs to the syntax highlighter.\n"
    " ~~~~~~~~~~~~~~~~^ -> \033[33m\033[1mNOTE: All other options concering the syntax-highlighter must come before the command itself.\033[0m\n"
    "--disable-comments:       Hides the comment."
    "\n--disable-commenthash:    Hides the \'#\' but still shows the comment."
    "\n--line-number:            Shows the current line.\n"
    "\n(Misc Commands)"
    "\n--precision-halt:         Shows the exact place where the halt happend.\n"
    "\n--memory-dump:            Shows the current state of memory at the end of the program.\n"
    "  ~~~~~~~~~~~^ -> \033[33m\033[1mNOTE: The Yellow-Colored byte is the current location of the pointer.\033[0m\n"
    "--snapshot-mem            Saves snapshot of memory if the interpreter encounters the character $1.\n"
    "--fullmemory-dump         Displays the entire state of the memory at the end of the program from 0 to the last cell.\n"
    "--syn-help                Displays the syntax help.\n"
    "--sp-syn-help             Displays the higher syntax help level.\n"
    "--snapshot-tok            Will attribute a new snapshot token from the input (NOT A POSITIONAL ARGUMENT).\n"
    "~~~~~~~~~~~~~^ \033[33m\033[1mNOTE: \'--snapshot-tok\' must come after \'--snapshot-mem\'\033[0m";
    return hlp;
}

std::string* initsynhelp(const int& level){
    std::string* o = new std::string("");
    if(level == 0){
        // basic syntax.
        (*o) = 
        "Brainfuck syntax:\n"
        "+------------+-------------------------------------------------------------------------------------------+\n"
        "|   Syntax   |  Utility                                                                                  |\n"
        "+------------+-------------------------------------------------------------------------------------------+\n"
        "|    \'>\'     | Moves 1 cell to the right                                                                 |\n"
        "|    \'<\'     | Moves 1 cell to the left                                                                  |\n"
        "|    \'+\'     | Increments by one the current cell                                                        |\n"
        "|    \'-\'     | Decrements by one the current cell                                                        |\n"
        "|    \'[\'     | Starts a loop, if the cell is zero, skip to the next \']\'                                  |\n"
        "|    \']\'     | Ends a loop, if the cell isn\'t zero, return to the previous \'[\'                           |\n"
        "|    \'.\'     | Outputs the value of the cell as ASCII to the standard output                             |\n"
        "|    \',\'     | Receives input as ASCII and sets the cell as the equivalent value (eg: \'A\' = 65)          |\n"
        "+------------+-------------------------------------------------------------------------------------------+\n"
        ;
    }

    if(level == 1){
        (*o) = 
        "Advanced Brainfuck syntax:\n"
        "+----------+------------------------------------------------------------------------------------------+\n"
        "|  Syntax  |  Utility                                                                                 |\n"
        "+----------+------------------------------------------------------------------------------------------+\n"
        "|   \'#\'    | Ignores everything that comes after it until it reaches a new line                       |\n"
        "|   \'%\'    | Takes a memory snapshot each time it is executed                                         |\n"
        "|   \'!\'    | When reached, it breaks the program, forces a quit even if the program did not finish    |\n"
        "+----------+------------------------------------------------------------------------------------------+\n"
        ;
    }
    return o;
}
