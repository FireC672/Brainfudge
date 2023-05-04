#ifndef MEM_INCLUDED_HPP
#define MEM_INCLUDED_HPP 

//typedef unsigned char unsigned char;
struct mem_snapshot{
    unsigned char* memory; 
    int current_loc;
    int memory_len;
};

#endif