#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

//Very simple test to make sure that when thread_yield is called
//in the only runnable thread, that thread is selected again immediately.
//Check the log file to make sure it shows scheduled/stopped correctly.
//This is set up to run with FIFO, but should work with SJF too.

/* Expected output:

In f1
Yielding
I'm still f1!
Exiting f1
*/

void f1() {
    printf("In f1\n");
    printf("Yielding\n");
    thread_yield();
    printf("I'm still f1!\n");
    printf("Exiting f1\n");
}

int main(int argc, char* argv[]) {
    if(thread_libinit(FIFO) == -1) {
        printf("Error initializing the thread library\n");
        exit(-1);
    }

    int tid = thread_create(f1, NULL, 0);

    thread_join(tid);

    thread_libterminate();
}
