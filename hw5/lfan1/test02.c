// C file for testing:
// 4. several odd-sized allocations
// 6. worstfit allocation
// 10. odd-sized allocation and free
// 12. initialize and round up to 1 page
// 13. no space left to allocate
// @author Li Fan

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>


int main(){
    int result = Mem_Init(100); // i printed number of pages in my library functions to check the roundup
    assert(result == 0);
    int *ptr;
    long *ptr_long;
    Mem_Dump();
    printf("--start allocating.\n");
    ptr = (int *) Mem_Alloc(sizeof(int)*2+1);
    assert(ptr != NULL);
    assert(((long) ptr) % 8 == 0);
    Mem_Dump();
    ptr_long = (long *) Mem_Alloc(sizeof(long)*2+1);
    assert(ptr_long != NULL);
    assert(((long) ptr_long) % 8 == 0);
    assert(ptr != NULL);
    assert(((long) ptr) % 8 == 0);
    Mem_Dump();

    printf("\n");
    printf("----freeing the smaller chunk----\n");
    result = Mem_Free(ptr, 0);
    assert(result == 0);
    Mem_Dump();
    printf("--start allocating one size of int, and checking if worst fit chooses the largest free area.\n");
    ptr = (int *) Mem_Alloc(sizeof(int));
    Mem_Dump();
    printf("--start allocating size that is too big to fit.\n");
    long *ptr_big;
    ptr_big = (long *) Mem_Alloc(sizeof(long)*8000+1);
    assert(ptr_big == NULL);
    printf("PASSED\n");

    return 0;
}
