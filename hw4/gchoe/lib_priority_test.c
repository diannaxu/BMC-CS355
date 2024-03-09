/**
 * Author: gchoe
 * Purpose: Simple test to ensure the library (libinit and libterminate)
 * works accordingly with PRIORITY.
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

int main() {
    if (thread_libinit(PRIORITY) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with PRIORITY initialized successfully.\n");

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with PRIORITY terminated successfully.\n");

    exit(EXIT_SUCCESS);
}