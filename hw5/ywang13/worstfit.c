//
// Created by Yuxiao Wang on 11/10/19.
// test worst-fit
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

#define COALESCE_NONE 0
#define COALESCE_ALL 1
#define COALESCE_LOCAL 2

int main() {
    assert(Mem_Init(1) == 0);
    void* p1 = Mem_Alloc(3000);
    assert(p1);
    void* p2 = Mem_Alloc(1000);
    assert(p2);
    assert(Mem_Free(p1, COALESCE_NONE) == 0);
    assert(Mem_Free(p2, COALESCE_NONE) == 0);
    assert(Mem_Alloc(1000));
    assert(Mem_Alloc(3000) == NULL);
    assert(m_error == E_NO_SPACE);

    printf("passed\n");
    exit(EXIT_SUCCESS);
}
