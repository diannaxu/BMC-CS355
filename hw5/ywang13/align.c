//
// Created by Yuxiao Wang on 11/10/19.
// test simple allocation, alignment, and free
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

int main() {
    assert(Mem_Init(1) == 0);

    // 8-byte alignment
    void* p1 = Mem_Alloc(1);
    assert(p1);

    // 8-byte allocation
    void* p2 = Mem_Alloc(8);
    assert(p2);
    void* p3 = Mem_Alloc(8);
    assert(p3);

    // some other sized allocation
    void* p4 = Mem_Alloc(16);
    assert(p4);
    void* p5 = Mem_Alloc(32);
    assert(p5);
    void* p6 = Mem_Alloc(25);
    assert(p6);

    // free


    Mem_Dump();
    printf("passed\n");
    exit(EXIT_SUCCESS);
}
