//Author: Ben Jiang
//Tests several odd-sized allocations

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 5

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    void *pointers[LENGTH]; 
    pointers[0] = Mem_Alloc(34);
    pointers[1] = Mem_Alloc(235);
    pointers[2] = Mem_Alloc(2347);
    pointers[3] = Mem_Alloc(3);
    pointers[4] = Mem_Alloc(55);
    for(int i = 0; i < LENGTH; i++){
        if(!pointers[i]){return EXIT_FAILURE;}
    }

    return EXIT_SUCCESS;

}