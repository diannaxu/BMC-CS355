#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 6
void f(void *arg) {
    printf("%s\n", (char*)arg);
}

void g(void *arg) {
    printf("%s\n", (char*)arg);
    if (thread_libterminate() == -1){
        printf("Failed on libterminate during thread\n");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    //initialize the library
    if (thread_libinit(PRIORITY) == -1) {
        printf("Failed on libinit\n");
        exit(EXIT_FAILURE);
    }
    //initialize tids and arg
    char msg[] = "Hello, world!";
    int tids[THREAD_NUMBER];
    //create 3 f threads and 3 g threads
    for (int i = 0; i < THREAD_NUMBER; i++) {
        if (i % 2 == 0) tids[i] = thread_create(f, msg, 0);
        else tids[i] = thread_create(g, msg, 0);
    }
    //join threads
    for (int i = 0; i < THREAD_NUMBER; i++) {
        if (thread_join(tids[i]) == -1){
            printf("Failed on thread join %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    //libterminate should have already occurred
    if (thread_libterminate() != -1){
        printf("Failed on libterminate\n");
        exit(EXIT_FAILURE);
    }
    printf("Completed tests. Depending on selection order, f test(s) and 1 g test should run before calling libterminate\n");
    exit(EXIT_SUCCESS);
}
