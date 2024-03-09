// file: priority_init_test.c

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int main(void) {
    printf("Priority Initialization Test\n");

    // Attempt to initialize the thread library with PRIORITY scheduling policy
    int result = thread_libinit(PRIORITY);

    if (result == 0) {
        printf("Priority Initialization Test Passed: Successfully initialized with PRIORITY scheduling policy.\n");
    } else {
        printf("Priority Initialization Test Failed: Unable to initialize with PRIORITY scheduling policy.\n");
    }

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
