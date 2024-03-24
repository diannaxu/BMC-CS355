//testing coalescing free space expect there to be one header the size of the region at the top with no pointers as there is only one thing in free list
#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    Mem_Init(1);  
    void * first = Mem_Alloc(8);
    Mem_Free(first, 0);
    void * second = Mem_Alloc(8);  
    Mem_Free(second, 1);
    Mem_Dump();

    return EXIT_SUCCESS;
    //check the mem_dump make  sure the first header is the size of the region + padding - HS
}