#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Mem_Init(1000000000000000);
    if(m_error == E_BAD_ARGS){
        printf("Bad Args\n");
    }
    Mem_Init(1);
    Mem_Init(1);
    if(m_error == E_BAD_ARGS){
        printf("Already Init\n");
        return EXIT_SUCCESS;
    }
}