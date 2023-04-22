#ifndef MEM_INCLUDED_HPP
#define MEM_INCLUDED_HPP 

typedef unsigned char byte;
struct mem_snapshot{
    byte* memory; 
    int current_loc;
    int memory_len;
};

mem_snapshot* save_snapshot(byte* m, int ptr, int len);

#endif