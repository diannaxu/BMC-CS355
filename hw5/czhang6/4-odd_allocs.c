// Test 4: allocating memory of several odd sizes
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(1024) == FAIL){
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(15);
    void *ptr2 = Mem_Alloc(27);
    void *ptr3 = Mem_Alloc(41);

    if(ptr1 == NULL){
        printf("Can't alloc ptr1\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Pointer 1 address: %p\n", ptr1);
    }

    if(ptr2 == NULL){
        printf("Can't alloc ptr2\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Pointer 2 address: %p\n", ptr2);
    }
    
    if(ptr3 == NULL){
        printf("Can't alloc ptr3\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Pointer 3 address: %p\n", ptr3);
    }

    return 0;
}
