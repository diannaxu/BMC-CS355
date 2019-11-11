//
// Created by Yuxiao Wang on 11/10/19.
// request allocation until out of space
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
    assert(Mem_Init(10000) == 0);
    srandom(time(NULL));
    while(Mem_Alloc((long) random() % 50 + 1));
    assert(m_error == E_NO_SPACE);
    Mem_Dump();
    printf("passed\n");
    exit(EXIT_SUCCESS);
}
