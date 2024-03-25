/*
    author: Yue Chen
    A test for Free and Coalesce
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

    printf("Testing several odd-sized allocation\n");
    void* ptr1 = Mem_Alloc(15);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    void* ptr2 = Mem_Alloc(15);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    void* ptr3 = Mem_Alloc(15);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    void* ptr4 = Mem_Alloc(15);
    if(m_error==E_NO_SPACE){
        printf("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    printf("\nFree 0:\n");
    Mem_Free(ptr1,0);
    Mem_Free(ptr2,0);
    Mem_Free(ptr3,0);
    Mem_Dump();
    printf("\nFree 1: Testing coalesce of free space\n");
    Mem_Free(NULL,1);
    Mem_Dump();

    printf("\nTesting worstfit allocation\n");
    void* wf = Mem_Alloc(24);
    printf("The newly-allocated memory should be after the chunk with 16 bytes\n");
    Mem_Dump();

    printf("\nFree 2: Testing coalesce within neighborhood\n");
    Mem_Free(wf,0);
    Mem_Free(ptr4,2);
    Mem_Dump();

}