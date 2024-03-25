//Author: Ben Jiang
//Tests full coalesce with one allocated hole in the middle

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 7
#define FAIL -1

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH];
    
    pointers[0] = Mem_Alloc(32);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    pointers[3] = Mem_Alloc(32);
    pointers[4] = Mem_Alloc(32);
    pointers[5] = Mem_Alloc(32);
    pointers[6] = Mem_Alloc(32);

    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }
    
    Mem_Free(pointers[0],NO_COALESCE);
    Mem_Free(pointers[1],NO_COALESCE);
    Mem_Free(pointers[2],NO_COALESCE);
    //Mem_Free(pointers[3],NO_COALESCE); 
    Mem_Free(pointers[4],NO_COALESCE);
    Mem_Free(pointers[5],NO_COALESCE);
    Mem_Free(pointers[6],FULL_COALESCE);

    if(!Mem_Alloc(4064)){return EXIT_FAILURE;} //should have a big enough hole for this (4096 minus header size, 32 in my case)

    return EXIT_SUCCESS;
}