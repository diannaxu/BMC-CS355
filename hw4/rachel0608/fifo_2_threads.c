// Simple two threads FIFO with yield
// Dianna xu

/* Expected output
thread 0: hello
thread 1: hello
thread 0: hello
thread 1: hello
thread 0: hello
thread 1: hello
terminate
*/

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void test(void* arg) {
    int id = *(int *) arg;
    for (int i = 0; i < 3; i++) {
        printf("thread %d: hello\n", id);
    }
}

int main() {
    thread_libinit(FIFO);
    int t0, t1;
    int a0 = 0;
    int a1 = 1;
    t0 = thread_create(test, &a0, 0);
    t1 = thread_create(test, &a1, 0);
    thread_join(t0);
    thread_join(t1);
    printf("terminate\n");
    if (thread_libterminate() == FAIL)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
