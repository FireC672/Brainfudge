/*
   NOTE: this code is open-source and free from warranty,
   the project is under the GNU General Public license, 
   The cloned or fork repo of the project must come with the GNU General
   Public License.
*/

#include <iostream>
#include <cassert>
#include <fstream>

int main(int argc, char** argv){
    // If there are no arguments, then exist.
    if(argc < 2){
        std::cerr << "\033[31m\033[1merror: \033[0mNot enough arguments.\n";
        return 1;
    }
    std::ifstream infile; 
    infile.open(argv[1],std::ios_base::in);
    
    // If the file is 'Imaginary' then exit.
    if(!infile){
       std::cerr << "\033[31m\033[1merror: \033[0mProvided source file is nonexistant.\n";
       return 2;
    }

    infile.close();
    return 0;
}