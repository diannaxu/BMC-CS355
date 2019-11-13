/* Author: Ruikang Shi
 * Some misuse and bad argument
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define SUCCESS 0
#define FAILURE -1



int main() {
    int result = Mem_Free(NULL,1);
    assert(result == FAILURE);

    result = Mem_Init(-1);
    assert(result == FAILURE);

    result = Mem_Init(1);
    assert(result == SUCCESS);

    result = Mem_Init(1);
    assert(result == FAILURE);

    result = Mem_Free(NULL,1);
    assert(result == SUCCESS);

    printf("PASS!\n");
    return EXIT_SUCCESS;
}