/* Author: Ruikang Shi
 * First we request a 4096-byte block, then seperately allocate a 1000-byte block and a 3000-byte one.
 * Then we free both blocks, and do it a again. Since we do as Worst-Fit, the second time we will allocate 1000-byte
 * in the 3000 byte section and we cannot allocate the 3000-byte anymore.
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#define REGION 4000
#define SUCCESS 0
#define FAILURE -1
#define SIZE1 1000
#define SIZE2 3000



int main() {

    int result = Mem_Init(REGION);
    assert(result == SUCCESS);

    void* first = Mem_Alloc(SIZE1);
    if (first == NULL){
        printf("Allocate fail\n");
    }
    void* second = Mem_Alloc(SIZE2);
    if (second == NULL){
        printf("Allocate fail\n");
    }

    result = Mem_Free(first,0);
    assert(result == SUCCESS);
    result = Mem_Free(second,0);
    assert(result == SUCCESS);

    first = Mem_Alloc(SIZE1);
    if (first == NULL){
        printf("Allocate fail\n");
    }
    second = Mem_Alloc(SIZE2);
    assert(second == NULL);
    assert(m_error == E_NO_SPACE);

    printf("PASS!\n");
    return EXIT_SUCCESS;
}