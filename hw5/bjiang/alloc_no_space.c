//Author: Ben Jiang
//Tests the case when there is no free space left for allocation / not a big enough hole

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 6

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH];
    pointers[0] = Mem_Alloc(64);
    pointers[1] = Mem_Alloc(32);
    pointers[2] = Mem_Alloc(32);
    pointers[3] = Mem_Alloc(4096); //has no space 
    pointers[4] = Mem_Alloc(3808); //fills the hole 
    for(int i = 0; i < 3; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }

    pointers[5] = Mem_Alloc(32); //the stack is full so should return NULL

    if(pointers[3] != NULL || pointers[5] != NULL){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}