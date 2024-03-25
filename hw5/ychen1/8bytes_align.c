/*
    author: Yue Chen
    A test for simple functions: 8-bytes Alignment and Free(0)
*/
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#define FAIL -1

int main(){

    if(Mem_Init(1000)==FAIL){
        printf("Failed to initialize\n");
        exit(EXIT_FAILURE);
    }

    printf("\nTesting 8-byte alignment\n");
    void* ptr1 = Mem_Alloc(1);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Allocation Succeeded\n");
    }
    void* ptr2 = Mem_Alloc(1);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Allocation Succeeded\n");
    }
    printf("The address is %p, should ended with 0/8\n", ptr2);

    Mem_Dump();

    printf("\nTesting free\n");
    if(Mem_Free(ptr1,0)==FAIL){
        printf("Failed to free\n");
        exit(EXIT_FAILURE);
    }
    if(Mem_Free(ptr2,0)==FAIL){
        printf("Failed to free\n");
        exit(EXIT_FAILURE);
    }
    printf("Free Succeeded\n");
    Mem_Dump();

}