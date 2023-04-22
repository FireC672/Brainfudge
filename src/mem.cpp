#include "../prototypes/mem.hpp"

mem_snapshot* save_snapshot(byte* m, int ptr, int len){
    mem_snapshot* sn = new mem_snapshot();
    sn->memory=m;
    sn->memory_len=len; 
    sn->current_loc=ptr;
    return sn;
}