//
// Created by Yuxiao Wang on 11/10/19.
// test coalescing
//

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "mem.h"

#define COALESCE_NONE 0
#define COALESCE_ALL 1
#define COALESCE_LOCAL 2

int main() {
    assert(Mem_Init(12000) == 0);
    void** ptrs = Mem_Alloc(10 * sizeof(*ptrs));
    for (int i = 0; i < 10; ++i) {
        ptrs[i] = Mem_Alloc(1000);
    }
    assert(Mem_Alloc(3000) == NULL);

    for (int i = 2; i < 5; ++i) {
        assert(Mem_Free(ptrs[i], COALESCE_NONE) == 0);
    }
    assert(Mem_Alloc(3000) == NULL);

    assert(Mem_Free(ptrs[6], COALESCE_NONE) == 0);
    assert(Mem_Free(ptrs[5], COALESCE_LOCAL) == 0);
    void* p11 = Mem_Alloc(3000);
    assert(p11);
    assert(Mem_Free(p11, COALESCE_LOCAL) == 0);
    void* p12 = Mem_Alloc(4000);
    assert(p12);
    assert(Mem_Free(p12, COALESCE_NONE) == 0);
    assert(Mem_Alloc(5000) == NULL);
    assert(Mem_Free(NULL, COALESCE_ALL) == 0);
    assert(Mem_Alloc(5000));
    printf("passed\n");
    exit(EXIT_SUCCESS);
}
