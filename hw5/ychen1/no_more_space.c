/*
    author: Yue Chen
    A test for No more memory available
*/
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#define FAIL -1

int main(){

    if(Mem_Init(4096)==FAIL){
        printf("Failed to initialize\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    void *ptr;
    printf("\n");
    while(1){
        printf("Allocated 64 bytes\n");
        ptr = Mem_Alloc(64);
        if (m_error == E_NO_SPACE){
            printf("Error: Not enough space for allocation.\n");
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_FAILURE);
}
