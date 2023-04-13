/*
   NOTE: this code is open-source and free from warranty,
   the project is under the GNU General Public license, 
   The cloned or fork repo of the project must come with the GNU General
   Public License.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "fread.hpp"
#include "util.hpp"

bool haltbreak = false;
int haltpos = 0;

bool bIgnoreComments=false;
bool bIgnoreHalts=false;
bool bSignalHalt=true;
bool bDisplaySettings=false;
uint16_t memorysize = 1000;

int main(int argc, char** argv){
    // If there are no arguments, then exist.
    if(argc < 2){
        std::cerr << "\033[31m\033[1merror: \033[0mNot enough arguments.\n";
        return 1;
    }
    
    // Arguments parsing.
    for(int i = 1; i < argc; i++){
        std::string strarg = str_c(argv[i],strlen(argv[i]));
        if(strarg.compare("--ignore-comments"))bIgnoreComments=true;
        if(strarg.compare("--ignore-halts"))bIgnoreHalts=true;
        if(strarg.compare("--unsignal-halt"))bSignalHalt=false;
        if(strarg.compare("--prg-settings"))bDisplaySettings=true;
        if(strarg.compare("-m") || strarg.compare("--memory-alloc")){
            if(i+1 >= argc){
                std::cerr << "\033[31m\033[1merror: \033[0m\n" << argv[i] << " requires a second argument.\n";
                return 3;
            }
            uint16_t n_memorysize = str_int(argv[i+1]);
            memorysize=n_memorysize;
            if(n_memorysize == 0){
                std::cout << "\033[33m\033[1mwarning: \033[0mcan\'t allocate zero bytes, allocation size will be set to default.\n";
                memorysize=1000;
            }
        }
    }

    std::ifstream infile; 
    infile.open(argv[1],std::ios_base::in);
    
    // If the file is 'Imaginary' then exit.
    if(!infile){
       std::cerr << "\033[31m\033[1merror: \033[0mProvided source file is nonexistant.\n";
       return 2;
    }

    // The reason we allocate a pointer, is to prevent stack-space issues.
    std::string* filedata = new std::string("");
    while(!infile.eof())filedata->push_back(infile.get());
    std::string bdata = extract_syntax(*filedata,bIgnoreComments,bIgnoreHalts);
    delete filedata;
    infile.close();

    // When there are no instructions.
    // Don't bother allocating space for the program. 
    // Just exit (no error).
    if(bdata.size() == 0){
        std::cout << "\033[33m\033[1mwarning: \033[0mthe file doesn\'t contain any valid instructions.\nor instructions might be commented.\n";
        return 0;
    }
    
    /*We put this in this scope, so that we free up quickly the stack.*/
    {
        int loopchecked = check_loops(bdata);
        if(loopchecked != 0){
            if(loopchecked > 0){
                 std::cout << "\033[33m\033[1mwarning: \033[0msome loops don\'t have endings (" << loopchecked << " loop(s))\n";
            }else{
                 std::cout << "\033[33m\033[1mwarning: \033[0msome loops don\'t have beginnings (" << (loopchecked/-1) << " loop(s))\n";
            }
            return 0;
        }
    }

    // (DONE) TODO: make an option for the user to allocate manually memory. (with safety features).
    unsigned char* memory = new unsigned char[memorysize];
    unsigned char* ptr = memory;

    for(int i = 0; i < bdata.size(); i++){
        // The current problem with this bit of code, there can be segfaults.
        // Adopting this solution currently. after debugging.
        if(bdata[i]=='>' && ptr < &memory[memorysize-1])ptr++; 
        if(bdata[i]=='<' && ptr > memory)ptr--; 
        if(bdata[i]=='+')(*ptr)++;
        if(bdata[i]=='-')(*ptr)--;
        if(bdata[i]=='.')std::cout << (char)*ptr; 
        if(bdata[i]==',')std::cin >> *ptr;
        if(bdata[i]=='[' && (*ptr)==0)while(bdata[i]!=']')i++;
        if(bdata[i]==']' && *ptr)while(bdata[i]!='[')i--;
        if(bdata[i]=='!'){
            haltbreak=true;
            haltpos = i;
            break;
        }
    }

    if(haltbreak && bSignalHalt){
        std::cout << "\n\033[1m*Program ended because of intentional halt (user-end) at char " << haltpos+1 << "*\n";
    }

    if(bDisplaySettings){
        // Currently there is only one setting (but expect more).
        std::cout << "Allocated memory (kB): " << memorysize<<'\n'; 
    }

    std::cout << '\n';

    return 0;
}