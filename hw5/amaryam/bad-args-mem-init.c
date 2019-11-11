/*
 * Test #5
 * File: bad-args-mem-init.c
 * Purpose: see what happens when we send bad args to mem_init
 * Expected Result: Mem init should return FAILURE because of bad args
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

#define BLOCK -1
#define FAILURE -1

int main() {
    if(Mem_Init(BLOCK) == FAILURE) {
      printf("\n\t\t\t\tSuccess! Mem init returned FAILURE because of bad args\n\n");
      return EXIT_SUCCESS;
    }
    printf("\n\t\t\t\tmest Failed. Meminit did not return FAILURE\n\nm");
    return EXIT_FAILURE;
}
