#include "mem.hpp"
#include <vector>

void push_snapshot
     (byte* m, const int& cptr, const int& mlen, std::vector<mem_snapshot*>& snapshot_holder){

   mem_snapshot* ptrMemorySnapshotTake = new mem_snapshot(); 
   ptrMemorySnapshotTake->current_loc=cptr;
   ptrMemorySnapshotTake->memory_len=mlen; 
   ptrMemorySnapshotTake->memory = new unsigned char[mlen];
   memcpy(ptrMemorySnapshotTake->memory,m,mlen);
   snapshot_holder.push_back(ptrMemorySnapshotTake);
}

void clear_snapshotholder(std::vector<mem_snapshot*>& snapshot_holder){
    for(int i = snapshot_holder.size()-1;i >= 0; i++){
        delete[] snapshot_holder.at(i)->memory;
        delete snapshot_holder.at(i);
    }

    snapshot_holder.clear();
}