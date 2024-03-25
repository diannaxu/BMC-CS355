/*
    author: Yue Chen
    A test for functions: Simple Allocation and Free(2), Memory can be written
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
    Mem_Dump();
    int num = 8;
    printf("\nTesting simple 8-byte allocation\n");
    void* ptr = Mem_Alloc(8);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Allocation Succeeded\n");
    }
    printf("\nTesting memory can be written\n");
    ptr = &num;
    printf("The number is %d, should be 8\n",*(int*)ptr);
    Mem_Dump();
    
    if(Mem_Free(ptr,2)==FAIL){
        printf("Failed to free\n");
        exit(EXIT_FAILURE);
    }
    printf("Free Succeeded\n");
    Mem_Dump();

    if(Mem_Free(ptr,2)==FAIL){
        printf("Failed to free\n");
        //Should exit here
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);

}
