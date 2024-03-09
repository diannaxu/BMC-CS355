#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 100

void hello_world(void *arg) {
    printf("%s\n", (char*)arg);
}

int main(void) {
    //test libinit
    if (thread_libinit(FIFO) == -1) {
        printf("Failed on libinit\n");
        exit(EXIT_FAILURE);
    }
    //initialize tids and arg
    int tids[THREAD_NUMBER];
    char msg[] = "Hello, world!";
    //create THREAD_NUMBER threads
    for (int i = 0; i < THREAD_NUMBER; i++) {
        tids[i] = thread_create(hello_world, msg, 0);
    }
    //join threads
    for (int i = 0; i < THREAD_NUMBER; i++) {
        if (thread_join(tids[i]) == -1){
            printf("Failed on thread join %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    //libterminate
    if (thread_libterminate() == -1){
        printf("Failed on libterminate\n");
        exit(EXIT_FAILURE);
    }
    printf("Completed tests. Ensure log matches FIFO (scheduled, finished) in numerical order\n");
    exit(EXIT_SUCCESS);
}
