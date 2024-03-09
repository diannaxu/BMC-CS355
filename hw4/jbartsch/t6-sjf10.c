#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
#include <poll.h>

#define THREAD_NUMBER 10

void f(void *arg) {
    //random sleep between 200-400
    int random = (rand() % 200) + 200;
    poll(NULL, 0, random);
    printf("%s %d\n", (char*)arg, random);
}

int main(void) {
    //test libinit
    if (thread_libinit(SJF) == -1) {
        printf("Failed on libinit\n");
        exit(EXIT_FAILURE);
    }
    //initialize tids and arg
    int tids[THREAD_NUMBER];
    char msg[] = "slept";
    //create THREAD_NUMBER threads
    for (int i = 0; i < THREAD_NUMBER; i++) {
        tids[i] = thread_create(f, msg, 0);
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
    printf("Completed tests. Ensure log matches SJF\n");
    exit(EXIT_SUCCESS);
}
