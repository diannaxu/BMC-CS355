/**
 * test 1 - basic thread test
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Basic test with thread creation and execution. Creates one thread,
 *              executes the simple_thread_function, and main thread joins the created thread.
 * 
 * Expected output: 
 * 
 * test 1
 * running
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void simple_thread_function(void *arg) {
    printf("running\n");
}

int main() {
    if (thread_libinit(FIFO) == -1){
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 1\n");

    int tid = thread_create(simple_thread_function, NULL, 0);
    
    if (tid == -1) {
        printf("Can't create thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid) == -1) {
        printf("Can't join thread\n");
        exit(EXIT_FAILURE);
    }

    printf("done\n");

    if (thread_libterminate() == -1){
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
