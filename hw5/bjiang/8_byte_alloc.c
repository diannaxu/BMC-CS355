//Author: Ben Jiang
//Tests a simple 8-byte allocation and check if the memory is 8-byte aligned

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }

    void *temp = Mem_Alloc(8);
    if(!temp){
        return EXIT_FAILURE;
    }else if((long)temp % 8 != 0){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
