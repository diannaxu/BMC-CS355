//Author: Ben Jiang
//Tests several aligned allocations and frees

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 5

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH]; 
    pointers[0] = Mem_Alloc(8);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(128);
    pointers[3] = Mem_Alloc(16);
    pointers[4] = Mem_Alloc(64);
    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }

    for(int i = 0; i < LENGTH; i++){
        if(Mem_Free(pointers[i],0) == FAIL){return EXIT_FAILURE;}
    }

    return EXIT_SUCCESS;

}