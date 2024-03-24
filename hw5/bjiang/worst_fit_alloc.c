//Author: Ben Jiang
//Tests allocations that fills the entire memory region

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 4

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH]; 
    pointers[0] = Mem_Alloc(64);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    pointers[3] = Mem_Alloc(3808);
    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }

    return EXIT_SUCCESS;

}