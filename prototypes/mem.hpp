#ifndef MEM_INCLUDED_HPP
#define MEM_INCLUDED_HPP 
#include <vector>

typedef unsigned char byte;
struct mem_snapshot{
    byte* memory; 
    int current_loc;
    int memory_len;
};

//mem_snapshot* save_snapshot(byte* m, int ptr, int len);


// Creates a memory snapshot at point 't', allocates it onto the heap, then push it onto the snapshot holder.
void push_snapshot
     (byte* m, const int& cptr, const int& mlen, std::vector<mem_snapshot*>& snapshot_holder);

// Automatically, clears the snapshot holder by deleting & freeing up memory
void clear_snapshotholder(std::vector<mem_snapshot*>& snapshot_holder);


#endif