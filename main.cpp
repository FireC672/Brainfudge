/*
   NOTE: this code is open-source and free from warranty,
   the project is under the GNU General Public license, 
   The cloned or fork repo of the project must come with the GNU General
   Public License.
*/

/*
 *  TODO: Do some refactoring, create specials functions for each action.
 *  TODO: Delete unused files or prototypes, probably rename some directories.
 *  TODO: Release a ELF executable and a Windows-Supported executable (i think i need docker.) 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include "prototypes/fread.hpp"
#include "prototypes/util.hpp"
#include "prototypes/helpdoc.hpp"
#include "prototypes/mem.hpp"

// Halt break: a flag that when set, force-exits the program,
// with return code.
bool haltbreak = false;
// Halt pos: when the 'haltbreak' flag is set, then 
// set it to the character position.
int haltpos = 0;

bool bIgnoreComments=false;
bool bIgnoreHalts=false;
bool bSignalHalt=true;
bool bDisplaySettings=false;
bool bCountInstructions=false;
bool bDisplayWhereHalt=false;
bool bDumpGeneralMemory=false;
bool bCustomMemoryDump=false;
bool bDumpGeneralMemory_entire=false;

// // If more than one character is inputed, then only fetch characters from a list instead of asking again.
//
// Custom memory dump things.

/* This hold snapshots of memory. */
std::vector<mem_snapshot*> snapshots;
/* This is the token that will trigger the snapshot */
char snapshot_token = '%';

// Only for syntax-highlight mode.
/* bDisplayCommentTag will show the '#' character before the comment. disable this, and it will be invisible*/
bool bDisplayCommentTags=true;
/* bDisplayComments will display all characters after '#', disabling this will render them invisible. */
bool bDisplayComments=true;
/* bDisplayLineNum will show the current line.*/
bool bDisplayLineNum=false;

// -----------

std::string inbuff;

// Allocated size.
// For incoming option '-m' 
uint16_t memorysize = 1000;

// Number of instructions.
// The reason we make it unsigned it because, 
// we can't have negative instructions.
uint32_t instructions=0;

// If the pointer is bigger than this value, then overwrite it with
// the current pointer value.
uint32_t max_reached=1;

// Offest is used in memory dump.
int offest=4;

int main(int argc, char** argv){
    // If there are no arguments, then exit.
    inbuff.clear();
    if(argc == 1){
        std::cerr << "\033[31m\033[1merror: \033[0mNot enough arguments.\n";
        return 1;
    }
    // Arguments parsing.
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i],"-help") || !strcmp(argv[i],"-h")){
            std::string* help = inithelp();
            std::cout << *help;
            delete help;
            return 0;
        }

        if(!strcmp(argv[i],"--ignore-comments"))
           bIgnoreComments=true;
        if(!strcmp(argv[i],"--ignore-halts"))   
           bIgnoreHalts=true;
        if(!strcmp(argv[i],"--unsignal-halt"))  
           bSignalHalt=false;
        if(!strcmp(argv[i],"--prg-settings"))
           bDisplaySettings=true;
        if(!strcmp(argv[i],"--count-instructions"))
           bCountInstructions=true;
        if(!strcmp(argv[i],"--line-number"))
           bDisplayLineNum=true;
        if(!strcmp(argv[i],"--precision-halt"))
           bDisplayWhereHalt=true;
        if(!strcmp(argv[i],"--memory-dump")){
            bDumpGeneralMemory = true;
            bDumpGeneralMemory_entire=false;
            offest=0;
        }

        if(!strcmp(argv[i],"--syn-help")){
            std::string* s = initsynhelp(0);
            std::cout << *s;
            delete s;
            return 0;
        }

           if(!strcmp(argv[i],"--sp-syn-help")){
            std::string* s = initsynhelp(1);
            std::cout << *s;
            delete s;
            return 0;
        }

        if(!strcmp(argv[i],"--fullmemory-dump")){
           bDumpGeneralMemory_entire=true;
           bDumpGeneralMemory=false;
        }

	if(!strcmp(argv[i],"--snapshot-tok")){
	   // NOTE: '--snapshot-tok' must come after '--snapshot-mem'
	   // because else will cause a segfault.
			
	    std::cout << "---- MODIFY SNAPSHOT TOKEN ----\n"; 
        std::cout << "Assign a new token (Must not be built-in. read \'--sp-syn-help\' or \'--syn-help\' for more info):\n";
        char nSnaptok; 
        std::cin >> nSnaptok;
           
	    // If token is built-in, then assert.
        if(isBuiltinToken(nSnaptok)){
	      std::cout << RED_CODE << BOLD_TEXT
	                << "fatal error: " << CLEAR_FLG  
                    << "Cannot assign a built-in token as snapshot token.\n";
	      return -4;
	    }
	    // Assign it.
        snapshot_token = nSnaptok;	   
        std::cout << "-------------------------------\n"; 
	}

        if(!strcmp(argv[i],"--snapshot-mem"))
            bCustomMemoryDump=true;
        
        if(!strcmp(argv[i],"-license") || !strcmp(argv[i],"-l")){
           std::cout << "Brainfudge Copyright (C) 2023 FireC672\n";
           std::cout << "This program comes with absolutely no WARRANTY\n"
                     << "This is free software, and you are welcome to redistribute it.\n"
                     << "Under certain conditions; type ./bfudge -lc for details.\n";
           return 0;
        }

        if(!strcmp(argv[i],"-lc")){
            std::ifstream license; 
            license.open("LICENSE",std::ios_base::in);
            if(!license){
                std::cout << "\033[33m\033[1mwarning: \033[0mThe source didn\'t came with any license.\n";
                std::cout << "Can't display proprer license terms and conditions.\n";
                return 1;
            }
            std::string currline;
            while(std::getline(license,currline)){
                currline.push_back('\n');
                std::cout << currline;
            }
            std::cout << '\n';
            license.close();
            return 0;
        }

        if(!strcmp(argv[i],"--disable-commenthash"))
           bDisplayCommentTags=false;
        if(!strcmp(argv[i],"--disable-comments"))
           bDisplayComments=false;
        
        // The syntax highlighter.
        if(!strcmp(argv[i],"--syntax-highlight")){
            std::ifstream infile; 
            infile.open(argv[1],std::ios_base::in);
            if(!infile){
               std::cerr << RED_CODE << BOLD_TEXT << "error: " << CLEAR_FLG << "Provided source file is nonexistant.\n";
               return 2;
            }
            
            std::string* data = new std::string("");
            data->clear();
            std::string currline; 
            while(std::getline(infile,currline)){
                currline.push_back('\n');
                for(auto& ch : currline)data->push_back(ch);
            }
            std::vector<int> loops = invalid_loops(*data); 
            infile.close();
            int currentline = 1;
            // Syntax highlighting.
            for(int i = 0; i < data->size(); i++){
                char token = data->at(i);
                std::cout << GREY_CODE;
                if(token == '>' || token == '<')std::cout << PURPLE_CODE;
                if(token == '+' || token == '-')std::cout << YELLOW_CODE;
                if(token == '.' || token == ',')std::cout << BLUE_CODE;
                if(token == '[' || token == ']'){
                    bool already = false;
                    {
                     std::vector<int>::iterator it; 
                     for(it = loops.begin(); it != loops.end();i++){
                        if(already)break;
                          if((*it)==i){
                             std::cout << BOLD_TEXT << RED_CODE;
                             already = true;
                             loops.erase(it);
                          }
                      }
                    }
                    if(!already)std::cout << BOLD_TEXT << CYAN_CODE;
                } 

                if(token == snapshot_token && bCustomMemoryDump)std::cout << BOLD_TEXT << YELLOW_CODE;

                if(token == '#' && !bIgnoreComments){
                    while(token != '\n' && i < data->size()){
                        token = data->at(i);
                        if(!bDisplayCommentTags && token == '#'){
                            token = data->at(i+1);
                            i++;
                        }
                        if(bDisplayComments) std::cout << BOLD_TEXT << GREEN_CODE << token << CLEAR_FLG;
                        i++;
                    }
                    i--;
                    continue;
                }

                if(token == '!' && !bIgnoreHalts)std::cout << BOLD_TEXT << RED_CODE;
                std::cout << token; 
                if(token == '\n' && bDisplayLineNum){
                    std::cout << YELLOW_CODE << currentline << ' ';
                    currentline++;
                }
                std::cout << CLEAR_FLG;
            }

            std::cout << '\n';
            delete data;
            return 0;
        }
    }

    std::ifstream infile; 
    infile.open(argv[1],std::ios_base::in);
    
    if(!infile){
       std::cerr << RED_CODE << BOLD_TEXT << "error: " << CLEAR_FLG << "Provided source file is nonexistant.\n";
       return 2;
    }

    // The reason we allocate a pointer, is to prevent stack-space limitation issues.
    std::string* filedata = new std::string("");
    while(!infile.eof())filedata->push_back(infile.get());
    std::string bdata = extract_syntax(*filedata,bIgnoreComments,bIgnoreHalts,snapshot_token,bCustomMemoryDump);
    delete filedata;
    infile.close();

    // When there are no instructions.
    // Don't bother allocating space for the program. 
    // Just exit (no error).
    if(bdata.size() == 0){
        std::cout << YELLOW_CODE << BOLD_TEXT <<"warning: " << CLEAR_FLG <<"the file doesn\'t contain any valid instructions.\nor instructions might be commented.\n";
        return 0;
    }
    
    /* We put this in this scope, so that we free up quickly the stack. */
    {
        /*
           check_loops() performs a for-loop.
           when we hit a '[' add 1.
           when we hit a ']' sub 1.

           if all loops are closed and started. 
           then we should receive a zero. 
           else, it's an error. 
        */
        int loopchecked = check_loops(bdata);
        if(loopchecked != 0){
            if(loopchecked > 0){
                std::cout << YELLOW_CODE << BOLD_TEXT << "warning: " << CLEAR_FLG << "Unmatched \']\' (" << loopchecked << ") loop(s))\n";
            }else{
                std::cout << YELLOW_CODE << BOLD_TEXT << "warning: " << CLEAR_FLG << "Unmatched \'[\' (" << (loopchecked/-1) << ") loop(s))\n";
            }
            return 0;
        }
    }

    // Allocate 'memory'
    byte_t* memory = new byte_t[memorysize];
    memset(memory,0,memorysize);
    // Set a pointer to the address (relative): 0.
    unsigned int ptr = 0;
    for(unsigned int i = 0; i < bdata.size(); i++){
        
        /* 
         Safety feature: if the pointer address is less than the Most-signficant byte,
         then increment.
         */
        if(bdata[i]=='>' && ptr < memorysize-1)ptr++; 

        if(bdata[i]=='<' && ptr > 0)ptr--; 

        if(ptr > max_reached)
           max_reached = ptr;
        
        if(bdata[i]=='+')memory[ptr]++;
        
        if(bdata[i]=='-')memory[ptr]--;

        if(bdata[i]=='.')std::cout << (char)memory[ptr]; 

        if(bdata[i]==','){
            if(inbuff.size() > 0){
               std::string _b = remove_slash(inbuff);
               std::string b = revstr(_b);
               char c = *b.end();
               inbuff.pop_back();
               memory[ptr]=c;
               continue;
            }

            std::cin >> inbuff;

            memory[ptr]=inbuff[0];
            
            if(inbuff == "\\n")memory[ptr]='\n';
            if(inbuff == "\\0")memory[ptr]=0x00; 
            if(inbuff == "\\t")memory[ptr]='\t';
            if(inbuff == "\\r")memory[ptr]='\r';
            if(inbuff == "\\b")memory[ptr]='\b';
            
        }

        if(bdata[i]=='['){
            if(memory[ptr]==0)while(bdata[i]!=']')i++;
        }

        if(bdata[i]==']'){
            if(memory[ptr]!=0)while(bdata[i]!='[')i--;
        }

        if(bdata[i]=='!'){
            haltbreak=true;
            haltpos = i;
            break;
        }

        if(bdata[i] == snapshot_token && bCustomMemoryDump){
            mem_snapshot* sn = new mem_snapshot();
            sn->memory = new unsigned char[max_reached];
            sn->memory_len=max_reached;
            sn->current_loc=ptr;
            memcpy(sn->memory,memory,max_reached);
            snapshots.push_back(sn);
        }

        instructions++;
    }

    if(haltbreak && bSignalHalt){
        std::cout << "\n" << BOLD_TEXT << "*Program ended because of intentional halt (user-end) at char " << haltpos+1 << "*\n";
        if(bDisplayWhereHalt==true){
           for(int i = 0; i < 3; i++){
             std::cout << bdata[3+haltpos];
           }         
        }
    }

    if(bCountInstructions){
        std::cout << "\nFinished " << BOLD_TEXT << CYAN_CODE << instructions << CLEAR_FLG << " instructions.\n";
    }
    
    if(bDumpGeneralMemory){
        std::cout << "\n\n\n+--------------------------------------------+\n";
        std::cout << "| "<< BOLD_TEXT << "Dumped Memory (hexmode):\n" << CLEAR_FLG;
        if(max_reached == 0){
            printf("\t General Memory dump is empty.\n");
        }else {
            printf("|  %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,0,CLEAR_FLG);
            for(int i = 0; i < max_reached+offest+1;i++){
              if(i%10 == 0 && i!=0)printf("  |\n|  %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,i,CLEAR_FLG);
              if(i+1 == ptr+1)printf("%s%s",BOLD_TEXT,YELLOW_CODE);
              printf("%.2x ",memory[i]);
              printf(CLEAR_FLG);
            }
            std::cout << "\n+--------------------------------------------+\n";
            printf("\nLast pointer location: %i (0x%x)\n",ptr,ptr);
        }

        printf("\n\n");
        printf("%sSnapshots (%lu): %s\n",BOLD_TEXT,snapshots.size(),CLEAR_FLG);
        
        int nSnapshotC = 1;

        for(auto& snapshot : snapshots){  
            std::cout << "\n\n+-----------------------------------------+\n";
            printf("| %sSnapshot_%i: %s",BOLD_TEXT,nSnapshotC,CLEAR_FLG);
            if(snapshot->memory_len == 0){
                printf("\n\tSnapshot empty.\n");
            }else {
                printf("\n| %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,0,CLEAR_FLG);
                for(int i = 0; i < snapshot->memory_len+1 ;i++){
                  if(i%10 == 0 && i!=0)printf("|\n| %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,i,CLEAR_FLG);
                  if(i+1 == snapshot->current_loc+1)printf("%s%s",BOLD_TEXT,YELLOW_CODE);
                  printf("%.2x ",snapshot->memory[i]);
                  printf(CLEAR_FLG);
                }   
                std::cout << "\n+-----------------------------------------+\n";
                printf("\nLast pointer location: %i (0x%x)\n",snapshot->current_loc,snapshot->current_loc);
            }

            nSnapshotC++;
            printf("\n");
        }
    }

    if(bDumpGeneralMemory_entire){
        std::cout << "\n\n\n+--------------------------------------------+\n";
        std::cout << "| "<< BOLD_TEXT << "Dumped Memory (hexmode):\n" << CLEAR_FLG;

        if(max_reached == 0){
            printf("\t General Memory dump is empty.\n");
        }else {
            printf("|  %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,0,CLEAR_FLG);
            for(int i = 0; i < memorysize;i++){
              if(i%10 == 0 && i!=0)printf("  |\n|  %s%s%.8x: %s",GREEN_CODE,BOLD_TEXT,i,CLEAR_FLG);
              if(i+1 == ptr+1)printf("%s%s",BOLD_TEXT,YELLOW_CODE);
              printf("%.2x ",memory[i]);
              printf(CLEAR_FLG);
            }
            std::cout << "\n+--------------------------------------------+\n";
            printf("\nLast pointer location: %i (0x%x)\n",ptr,ptr);
       }
    }
    
    // free up the snapshots. 
    while(!snapshots.empty()){
        delete (*(snapshots.end()))->memory;
        delete (*(snapshots.end()));
        snapshots.pop_back();
    }

    snapshots.clear();
    std::cout << '\n';
    delete[] memory;
    return 0;
}
