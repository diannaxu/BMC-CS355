//
// Created by Yuxiao Wang on 11/11/19.
// test if memory is writable and free works afterwards
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

#define COALESCE_NONE 0
#define COALESCE_ALL 1
#define COALESCE_LOCAL 2

struct Node {
    unsigned long size;
    struct Node* next;
};

int main() {
    assert(Mem_Init(1) == 0);
    struct Node* p1 = Mem_Alloc(sizeof(struct Node));
    p1->size = 10;
    p1->next = Mem_Alloc(sizeof(struct Node));
    p1->next->size = 20;
    p1->next->next = NULL;
    printf("expected: |node 10| -> |node 20| ->\n");
    printf("got: ");
    for (struct Node* cur = p1; cur; cur = cur->next) {
        printf("|node %ld| -> ", cur->size);
    }
    printf("\n");

    char* p2 = Mem_Alloc(8);
    for (int i = 0; i < 7; ++i) {
        p2[i] = (char) ('a' + i);
    }
    p2[7] = '\0';

    printf("expected: abcdefg\n");
    printf("got: %s\n", p2);

    int* p3 = Mem_Alloc(5 * sizeof(int));
    for (int i = 0; i < 5; ++i) {
        p3[i] = i;
    }
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += p3[i];
    }
    printf("expected: 10\n");
    printf("got: %d\n", sum);

    Mem_Dump();

    Mem_Free(p1, COALESCE_NONE);
    Mem_Free(p1->next, COALESCE_NONE);
    Mem_Free(p2, COALESCE_NONE);
    Mem_Free(p3, COALESCE_ALL);
    Mem_Dump();
    printf("should exist only one big free block\n");

    exit(EXIT_SUCCESS);
}

