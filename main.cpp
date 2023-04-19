/*
   NOTE: this code is open-source and free from warranty,
   the project is under the GNU General Public license, 
   The cloned or fork repo of the project must come with the GNU General
   Public License.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "fread.hpp"
#include "util.hpp"

bool haltbreak = false;
int haltpos = 0;

bool bIgnoreComments=false;
bool bIgnoreHalts=false;
bool bSignalHalt=true;
bool bDisplaySettings=false;
bool bCountInstructions=false;

// Only for syntax-highlight mode.
/* bDisplayCommentTag will show the '#' character before the comment. disable this, and it will be invisible*/
bool bDisplayCommentTags=true;
/* bDisplayComments will display all characters after '#', disabling this will render them invisible. */
bool bDisplayComments=true;
/* bDisplayLineNum will show the current line.*/
bool bDisplayLineNum;
// -----------

// Allocated size
uint16_t memorysize = 1000;

// Number of instructions.
// The reason we make it unsigned it because, we can't have negative instructions.
uint32_t instructions=0;


int main(int argc, char** argv){
    // If there are no arguments, then exist.
    if(argc < 2){
        std::cerr << "\033[31m\033[1merror: \033[0mNot enough arguments.\n";
        return 1;
    }
    // Arguments parsing.
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], ("--ignore-comments")))bIgnoreComments=true;
        if(!strcmp(argv[i],"--ignore-halts"))bIgnoreHalts=true;
        if(!strcmp(argv[i],"--unsignal-halt"))bSignalHalt=false;
        if(!strcmp(argv[i],"--prg-settings"))bDisplaySettings=true;
        if(!strcmp(argv[i],"--count-instructions"))bCountInstructions=true;
        if(!strcmp(argv[i],"--line-number"))bDisplayLineNum=true;
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

        if(!strcmp(argv[i],"--disable-commenthash"))bDisplayCommentTags=false;
        if(!strcmp(argv[i],"--disable-comments"))bDisplayComments=false;
        if(!strcmp(argv[i],"--syntax-highlight")){
            // '--syntax-highlight' performs like the 'cat' command but color-code valid syntaxes,
            // Comments are green (if --ignore-comment is disabled).
            // Halts are red (if --ignore-halt is disabled).
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
                    // Don't allocate much stack memory.
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
                if(token == '#' && !bIgnoreComments){
                    while(token != '\n' && i < data->size()){
                        token = data->at(i);
                        if(!bDisplayCommentTags && token == '#'){
                            token = data->at(i+1);
                            i++;
                        }
                        if(bDisplayComments) std::cout << BOLD_TEXT <<GREEN_CODE << token << CLEAR_FLG;
                        i++;
                    }
                    i--;
                    continue;
                }
                if(token == '!' && !bIgnoreHalts)std::cout << BOLD_TEXT << RED_CODE;
            
                std::cout << token; 
                std::cout << CLEAR_FLG;
                currentline++;
            }

            std::cout << '\n';
            delete data;
            return 0;
        }
    }

    std::ifstream infile; 
    infile.open(argv[1],std::ios_base::in);
    
    // If the file is 'Imaginary' then exit.
    if(!infile){
       std::cerr << RED_CODE << BOLD_TEXT <<"error: " << CLEAR_FLG << "Provided source file is nonexistant.\n";
       return 2;
    }

    // The reason we allocate a pointer, is to prevent stack-space limitation issues.
    std::string* filedata = new std::string("");
    while(!infile.eof())filedata->push_back(infile.get());
    std::string bdata = extract_syntax(*filedata,bIgnoreComments,bIgnoreHalts);
    delete filedata;
    infile.close();

    // When there are no instructions.
    // Don't bother allocating space for the program. 
    // Just exit (no error).
    if(bdata.size() == 0){
        std::cout << YELLOW_CODE << BOLD_TEXT <<"warning: " << CLEAR_FLG <<"the file doesn\'t contain any valid instructions.\nor instructions might be commented.\n";
        return 0;
    }
    
    /*We put this in this scope, so that we free up quickly the stack.*/
    {
        int loopchecked = check_loops(bdata);
        if(loopchecked != 0){
            if(loopchecked > 0){
                std::cout << YELLOW_CODE << BOLD_TEXT << "warning: " << CLEAR_FLG << "some loops don\'t have endings (" << loopchecked << " loop(s))\n";
            }else{
                std::cout << YELLOW_CODE << BOLD_TEXT << "warning: " << CLEAR_FLG << "some loops don\'t have beginnings (" << (loopchecked/-1) << " loop(s))\n";
            }
            return 0;
        }
    }
    byte_t* memory = new byte_t[memorysize];
    byte_t* ptr = memory;

    for(unsigned int i = 0; i < bdata.size(); i++){
        if(bdata[i]=='>' && ptr < &memory[memorysize-1])ptr++; 
        if(bdata[i]=='<' && ptr > memory)ptr--; 
        if(bdata[i]=='+')(*ptr)++;
        if(bdata[i]=='-')(*ptr)--;
        if(bdata[i]=='.')std::cout << (char)*ptr; 
        if(bdata[i]==',')std::cin >> *ptr;
        if(bdata[i]=='['){
            if((*ptr)==0)
            while(bdata[i]!=']')i++;
        }
        if(bdata[i]==']'){
            if((*ptr)!=0)while(bdata[i]!=']')i--;
        }
        if(bdata[i]=='!'){
            haltbreak=true;
            haltpos = i;
            break;
        }
        instructions++;
    }

    if(haltbreak && bSignalHalt){
        std::cout << "\n"<<BOLD_TEXT<<"*Program ended because of intentional halt (user-end) at char " << haltpos+1 << "*\n";
    }

    if(bCountInstructions){
        std::cout << "\nFinished " << BOLD_TEXT << CYAN_CODE << instructions << CLEAR_FLG << " instructions.\n";
    }

    std::cout << '\n';

    return 0;
}