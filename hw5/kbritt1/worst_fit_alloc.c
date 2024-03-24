//testing worst fit alloc, look at mem dump and there should be 3 headers instead of 2 as the largest chunk was split again
#include "../mem.h"
#include "stdio.h"
#include <stdlib.h>

int main(){
    Mem_Init(1);  
    void * first = Mem_Alloc(8);
    Mem_Free(first, 0);
    void * second = Mem_Alloc(8);  
    Mem_Dump();
    Mem_Free(second, 0);
    Mem_Free(first,0);
    if ((unsigned long) first < (unsigned long) second){
        printf("SUCCESS\n"); // first pointer should be lower in the mmap (I made it so the new free header is inserted after the allocated pointer ) second pointer should be higher
        return EXIT_SUCCESS;
    }

    printf("FAILURE\n");
    return EXIT_FAILURE;
}