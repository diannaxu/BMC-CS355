/**
 * test 2 - basic fifo test
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks whether threads are scheduled in the order of FIFO.
 *              Creates 2 threads, each will execute an unique thread func, 
 *              joins all threads in the order they were created.
 * 
 * Expected output: 
 * 
 * test 2
 * doing something!
 * doing something else!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void do_something(void *arg) {
    printf("doing something! \n");
}

void do_something(void *arg) {
    printf("doing something else! \n");
}

int main() {
    if (thread_libinit(FIFO) == -1){
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 2\n");

    int tid1 = thread_create(do_something, NULL, 0);
    int tid2 = thread_create(do_something, NULL, 0);

    if (tid1 == -1 || tid2 == -1) {
        printf("Can't create thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1) {
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
