//Author: Ben Jiang
//Tests one allocation and free

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define FAIL -1
int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    
    void *temp = Mem_Alloc(32);
    if(!temp){
        return EXIT_FAILURE;
    }

    if(Mem_Free(temp,0) == FAIL){return EXIT_FAILURE;}

    return EXIT_SUCCESS;

}