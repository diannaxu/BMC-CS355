/* Author: Ruikang Shi
 * Basic tests, test whether every function is usable and the memory is writable.
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#define REGION 4096
#define SUCCESS 0
#define FAILURE -1
#define SIZE1 32
#define SIZE2 200



int main() {
    int result = Mem_Init(REGION);
    assert(result == SUCCESS);

    int* ptr1 = (int*)Mem_Alloc(SIZE1);
    int* ptr2 = (int*)Mem_Alloc(SIZE2);

    *ptr1 = 1;
    *ptr2 = 2;

    result = Mem_Free(ptr1,0);
    assert(result == SUCCESS);
    result = Mem_Free(ptr2,1);
    assert(result == SUCCESS);
    result = Mem_Free(NULL,0);
    assert(result == SUCCESS);

    printf("PASS!\n");
    return EXIT_SUCCESS;
}