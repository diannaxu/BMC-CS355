/* Author: Ruikang Shi
 * Mem_Init(1) should give it one pagesize memory, which is 4096, then we allocate as many 8-byte as possible, each with its header.
 * So we should have allocate 102 blokcs.
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define SPACENEED 1
#define BYTE 1



int main() {
    int result = Mem_Init(SPACENEED);
    assert(result == 0);

    int count = 0;
    void* ptr;
    while (true){
        ptr = Mem_Alloc(BYTE);
        if (ptr == NULL){
            break;
        }
        count ++;
    }
    printf("Allocated blocks: %d\n",count);
    return EXIT_SUCCESS;
}