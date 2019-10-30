// Author: Ruikang
// Test for misusing, should run just fine without error.
#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 10000
#define FAILURE -1

void foo(void* arg) {
}

int main(int argc, char** argv) {
    if (thread_create(foo,NULL,0) == FAILURE) {
        printf("This line should appear: create before init\n");
    }

    if (thread_join(FAILURE) == FAILURE) {
        printf("This line should appear: join before init\n");
    }

    if (thread_yield() == FAILURE) {
        printf("This line should appear: yield before init\n");
    }

    if (thread_libterminate() == FAILURE) {
        printf("This line should appear: terminate before init\n");
    }

    if (thread_libinit(PRIORITY) == FAILURE) {
        printf("This line shouldn't appear\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libinit(PRIORITY) == FAILURE) {
        printf("This line should appear: double init\n");
    }

    if (thread_join(FAILURE) == FAILURE) {
        printf("This line should appear: join an invalid tid\n");
    }

    if (thread_libterminate() == FAILURE) {
        printf("This line shouldn't appear\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == FAILURE) {
        printf("This line should appear: double terminate\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}