/* Author: Ruikang Shi
 * First allocate 64 32-byte blocks in a 4096 heap. Then we use 3 different kinds of coalesce to test.
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#define REGION 4000
#define SUCCESS 0
#define FAILURE -1
#define SIZE1 32
#define SIZE2 200



int main() {
    void* ptr[64];
    int count = 0;
    int result = Mem_Init(REGION);
    assert(result == SUCCESS);

    while (true){
        ptr[count] = Mem_Alloc(SIZE1);
        if (ptr[count] == NULL){
            break;
        }
        count ++;
    }

    assert(count == 64);
    for (int i = 0; i<64;i++){
        if (i % 2 == 0){
            Mem_Free(ptr[i],0);
            ptr[i] = NULL;
        }
    }
    void* temp = Mem_Alloc(SIZE1+1);
    assert(temp==NULL);

    for (int i = 0; i<64;i++){
        if (i % 4 == 1){
            Mem_Free(ptr[i],2);
            ptr[i] = NULL;
        }
    }
    temp = Mem_Alloc(SIZE2);
    assert(temp==NULL);
    for (int i = 0; i<64;i++){
        if (i % 4 == 3){
            Mem_Free(ptr[i],2);
            ptr[i] = NULL;
        }
    }
    temp = Mem_Alloc(SIZE2);
    assert(temp==NULL);

    Mem_Free(NULL,1);
    temp = Mem_Alloc(REGION);
    assert(temp!=NULL);

    printf("PASS!\n");
    return EXIT_SUCCESS;
}