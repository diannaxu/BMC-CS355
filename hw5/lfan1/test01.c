// C file for testing:
// 1. check for 8-byte alignment
// 2. simple 8-byte allocation
// 3. a few aligned allocations
// 8. simple allocation and free 
// 9. aligned allocation and free
// 15. check that memory can be written to after allocation
// @author Li Fan

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>


int main(){
    int result = Mem_Init(200);
    assert(result == 0);
    int *ptr;
    long *ptr_long;
    Mem_Dump();
    printf("--start allocating.\n");
    ptr = (int *) Mem_Alloc(sizeof(int)*5);
    Mem_Dump();
    ptr_long = (long *) Mem_Alloc(sizeof(long)*2);
    assert(ptr != NULL);
    assert(((long) ptr) % 8 == 0);
    Mem_Dump();
    for (int i = 0; i < 5; i++) {
        *(ptr+i) = (i+1)*2;
    }
    for (int i = 0; i < 2; i++) {
        *(ptr_long+i) = (i+1)*5;
    }
    for (int i = 0; i < 5; i++) {
        printf("memory at location %p writable: %d\n", ptr+i, *(ptr+i));
    }
    for (int i = 0; i < 2; i++) {
        printf("memory at location %p writable: %ld\n", ptr_long+i, *(ptr_long+i));
    }
    printf("\n");
    printf("----start freeing----\n");
    result = Mem_Free(ptr, 0);
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(ptr_long, 0);
    assert(result == 0);
    Mem_Dump();
    printf("PASSED\n");

    return 0;
}