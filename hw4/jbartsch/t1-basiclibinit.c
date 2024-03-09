#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

static void f(void *arg) {
    printf("Mic check, 1, 2, 3\n");
}

int main(void) {
    //test libterminate before libinit
    if (thread_libterminate() != -1){
        printf("Failed on libterminate before libinit\n");
        exit(EXIT_FAILURE);
    }
    //now initialize the library
    if (thread_libinit(FIFO) == -1) {
        printf("Failed on libinit\n");
        exit(EXIT_FAILURE);
    }
    //create a thread with function f
    if (thread_create(f, NULL, 0) == -1){
        printf("Failed on thread_create\n");
        exit(EXIT_FAILURE);
    }
    //libterminate
    if (thread_libterminate() == -1){
        printf("Failed on libterminate\n");
        exit(EXIT_FAILURE);
    }
    printf("Completed tests. Log output should show one create.\n");
    exit(EXIT_SUCCESS);
}
