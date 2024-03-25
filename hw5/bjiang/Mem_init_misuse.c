//Author: Ben Jiang
//Tests misuse of Mem_Init()

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 5

int main(){
    if(Mem_Init(-3425) != FAIL){
        return EXIT_FAILURE;
    }
    if(Mem_Init(33) == FAIL){
        return EXIT_FAILURE;
    }
    if(Mem_Init(4545) != FAIL){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}