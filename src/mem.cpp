#include "mem.hpp"
#include <vector>

// mem_snapshot* push_snapshot (unsigned char* m, const int& cptr, const int& mlen){
//    mem_snapshot* ptrMemorySnapshotTake = new mem_snapshot(); 
//    ptrMemorySnapshotTake->current_loc=cptr;
//    ptrMemorySnapshotTake->memory_len=mlen; 
//    ptrMemorySnapshotTake->memory = new unsigned char[mlen];
//    memcpy(ptrMemorySnapshotTake->memory,m,mlen);
//    return ptrMemorySnapshotTake;
// }

// void clear_snapshotholder(std::vector<mem_snapshot*>& snapshot_holder){
//     for(int i = snapshot_holder.size()-1;i >= 0; i++){
//         delete[] snapshot_holder.at(i)->memory;
//         delete snapshot_holder.at(i);
//     }

//     snapshot_holder.clear();
// }