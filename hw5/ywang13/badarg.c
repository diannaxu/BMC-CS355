//
// Created by Yuxiao Wang on 11/10/19.
// test bad arguments
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

#define COALESCE_NONE 0
#define COALESCE_ALL 1
#define COALESCE_LOCAL 2

int main() {
    assert(Mem_Init(-1) == -1);
    void* p1 = Mem_Alloc(1);
    assert(p1 == NULL);
    assert(Mem_Free(p1, COALESCE_LOCAL) == -1);

    assert(Mem_Init(4096) == 0);
    assert(Mem_Init(4096) == -1);
    void* p2 = Mem_Alloc(-1);
    assert(p2 == NULL);

    printf("passed\n");
    exit(EXIT_SUCCESS);
}
