/*
    author: Yue Chen
    A test for Mem_Init
*/
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#define FAIL -1

int main(){

    printf("Initialize -1 memory\n");
    if(Mem_Init(-1)==FAIL){
        printf("Failed to initialize -1\n");
    }

    if(Mem_Init(1000)==FAIL){
        printf("Failed to initialize\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    printf("Testing call Mem_Init more than once\n");
    if(Mem_Init(1000)==FAIL){
        printf("Failed to initialize, behaved correctly\n");
        // should exit here
        exit(EXIT_SUCCESS);
    }else{
        printf("Initialization Succeeded, incorrectly\n");
    }

    exit(EXIT_FAILURE);

}