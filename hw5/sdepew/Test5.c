//
// Created by Sarah Depew on 3/26/18.
//

#include "../../mem.h"
#include "../../helper.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_ALLOC -112

/*
 * Testing for bad args to Mem_Init
 * Expected Behavior: Should have error for Mem_Init attempt
 */
int test_five() {
    int result = Mem_Init(NUM_ALLOC);
    if (result == ERROR) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}


int main() {
    exit(test_five());
}
