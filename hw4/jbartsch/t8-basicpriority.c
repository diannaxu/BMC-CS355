#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

#define THREAD_NUMBER 6
void f(void *arg) {
    printf("%s\n", (char*)arg);
}

void g(void *arg) {
    printf("%s\n", (char*)arg);
}

void h(void *arg) {
    printf("%s\n", (char*)arg);
}

int main(void) {
    //initialize the library
    if (thread_libinit(PRIORITY) == -1) {
        printf("Failed on libinit\n");
        exit(EXIT_FAILURE);
    }
    //initialize tids and arg
    char msgF[] = "f";
    char msgG[] = "g";
    char msgH[] = "h";
    int tids[THREAD_NUMBER];
    //create 2 of f, g, and h
    for (int i = 0; i < THREAD_NUMBER; i+=3) {
        tids[i] = thread_create(f, msgF, 1);
        tids[i+1] = thread_create(g, msgG, 0);
        tids[i+2] = thread_create(h, msgH, -1);
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
    printf("Completed tests. Should complete threads in priority f, g, h: 0/3, 1/4, 2/5.\n");
    exit(EXIT_SUCCESS);
}
