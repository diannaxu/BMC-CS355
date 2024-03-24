//Author: Ben Jiang
//Tests local coalesce and full coalesce

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 3
#define FAIL -1

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH]; 
    pointers[0] = Mem_Alloc(64);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }
    for(int i = 0; i < LENGTH-1; i++){
        if(Mem_Free(pointers[i],0) == FAIL){
            return EXIT_FAILURE;
        }
    }
    if(Mem_Free(pointers[LENGTH-1],2) == FAIL){
        return EXIT_FAILURE;
    }

    pointers[0] = Mem_Alloc(64);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    for(int i = 0; i < LENGTH-1; i++){
        if(Mem_Free(pointers[i],0) == FAIL){
            return EXIT_FAILURE;
        }
    }
    if(Mem_Free(NULL,1) == FAIL){ //freeing NULL pointer
        return EXIT_FAILURE;
    }
    pointers[0] = Mem_Alloc(64);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    for(int i = 0; i < LENGTH; i++){
        if(Mem_Free(pointers[i],0) == FAIL){
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;

}