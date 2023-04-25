#ifndef MEM_INCLUDED_HPP
#define MEM_INCLUDED_HPP 
#include <vector>

//typedef unsigned char unsigned char;
struct mem_snapshot{
    unsigned char* memory; 
    int current_loc;
    int memory_len;
};

//mem_snapshot* save_snapshot(unsigned char* m, int ptr, int len);


// Creates a memory snapshot at point 't', allocates it onto the heap, then push it onto the snapshot holder.
mem_snapshot* push_snapshot
     (unsigned char* m, const int& cptr, const int& mlen);

// Automatically, clears the snapshot holder by deleting & freeing up memory
//void clear_snapshotholder(std::vector<mem_snapshot*>& snapshot_holder);


#endif