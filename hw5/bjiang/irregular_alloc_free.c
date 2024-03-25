//Author: Ben Jiang
//Tests several odd-sized allocations and frees

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 5

int main(){

    if(Mem_Init(242) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH]; 
    pointers[0] = Mem_Alloc(355);
    pointers[1] = Mem_Alloc(31);
    pointers[2] = Mem_Alloc(1);
    pointers[3] = Mem_Alloc(353);
    pointers[4] = Mem_Alloc(98);
    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }

    for(int i = 0; i < LENGTH; i++){
        if(Mem_Free(pointers[i],0) == FAIL){return EXIT_FAILURE;}
    }

    return EXIT_SUCCESS;

}