/*
Written by: Maya Johnson
Test of the different levels of coalescing
*/

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main(int argc, char *argv[]) {
    //test if Mem_Init opens
    if(-1 == Mem_Init(400)) {
        printf("Error initializing memory\n");
        exit(0);
    }

    printf("\nEverything should be free\n");
    Mem_Dump();

    void *ptr1 = Mem_Alloc(sizeof(void*));
    void *ptr2 = Mem_Alloc(sizeof(void*));
    void *ptr3 = Mem_Alloc(sizeof(void*));
    void *ptr4 = Mem_Alloc(sizeof(void*));

    printf("\nThings should be less free\n");
    Mem_Dump();

    Mem_Free(ptr2, 2);
    Mem_Free(ptr3, 2);
    printf("\nThings should be a little more free (and coalesced a little)\n");
    Mem_Dump();

    Mem_Free(ptr1, 0);
    Mem_Free(ptr4, 0);
    printf("\nThings should be more free, but not more coalesced\n");
    Mem_Dump();

    Mem_Free(NULL, 1);
    printf("\nEverything should be freed now:\n");
    Mem_Dump();
}
