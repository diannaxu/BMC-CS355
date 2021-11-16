// C file for testing:
// several coelescing tests
// 14. try to free a NULL pointer (2 cases)
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
    int *ptr1;
    int *ptr2;
    int *ptr3;
    int *ptr4;
    int *ptr5;
    Mem_Dump();
    printf("---start allocating---\n");
    ptr1 = (int *) Mem_Alloc(sizeof(int)*3);
    ptr2 = (int *) Mem_Alloc(sizeof(int)*5);
    ptr3 = (int *) Mem_Alloc(sizeof(int)*7);
    ptr4 = (int *) Mem_Alloc(sizeof(int)*9);
    ptr5 = (int *) Mem_Alloc(sizeof(int)*11);
    Mem_Dump();

    printf("---start freeing---\n");
    result = Mem_Free(ptr1, 0); // no coelescing
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(ptr3, 0); // no coelescing
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(ptr4, 2); // local coelescing
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(ptr5, 0); // global coelescing
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(ptr2, 0); // no coelescing 
    assert(result == 0);
    Mem_Dump();
    result = Mem_Free(NULL, 0); // bad arguments
    assert(result == -1);
    Mem_Dump();
    result = Mem_Free(NULL, 1); // global coelescing
    assert(result == 0);
    Mem_Dump();

    printf("PASSED\n");
    return 0;
}