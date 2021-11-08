// Elly Fernandez
/*Allocates memory for four 8-byte aligned blocks. Frees the last block and coalesces all*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mem.h"


// fills the memory with letters of the alphabet
void fillMem(char* ptr, int size) {
    for(int i = 0; i < size-1; i++) {
            //ptr[i] = (i+'a') % 27;
            ptr[i] = (i % 26)+ 'a';
    }
    ptr[size-1] = '\0';
}

int main(int argc, char** argv) {
    int status = Mem_Init(1024);
    assert(status == 0);
    // check that init was successful
    Mem_Dump();
    
    
    char* charPtr = Mem_Alloc(16);
    assert(charPtr != NULL);
    fillMem(charPtr, 16);
    printf("16 bytes: %s\n", charPtr);
    
    charPtr = Mem_Alloc(32);
    assert(charPtr != NULL);
    fillMem(charPtr, 32);
    printf("32 bytes: %s\n", charPtr);
    
    charPtr = Mem_Alloc(48);
    assert(charPtr != NULL);
    fillMem(charPtr, 48);
    printf("48 bytes: %s\n", charPtr);
    
    charPtr = Mem_Alloc(16);
    assert(charPtr != NULL);
    fillMem(charPtr, 16);
    printf("16 bytes: %s\n", charPtr);
    Mem_Dump();

    status = Mem_Free(charPtr, 1);
    assert(status == 0);
    Mem_Dump();
    return EXIT_SUCCESS;
}
