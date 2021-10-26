#include "userthread.c"
#include <stdio.h>
#include <stdlib.h>

int threadArgs[] = {1,2,3,4,5};

// This is a simple test that will print Hello each time a thread is joined. After
// creating 5 threads and then joining them, the joining of an invalid thread is attemped.
// This invalid join should result in a negative one. The library is terminated at the end
// so all memory should be freed.

/* Expected output

Thread with tid 1 was successfully created
Thread with tid 2 was successfully created
Thread with tid 3 was successfully created
Thread with tid 4 was successfully created
Thread with tid 5 was successfully created
Hello
Join status 1 for thread 1
Hello
Join status 2 for thread 2
Hello
Join status 3 for thread 3
Hello
Join status 4 for thread 4
Hello
Join status 5 for thread 5
Join status -1 for thread 32764 // this value is just whatever value you have next in memory
*/

// arg is the tid of the current thread
void whoseRunning(void *arg) {
    printf("Hello\n"); 
}

int main(int argc, char** argv) {
    if(thread_libinit(FIFO) == -1) {
        exit(-1);
    }
    int tids[5];

    for(int i = 0; i < 5; i++) {
        tids[i] = thread_create(whoseRunning, &threadArgs[i], 0);
        printf("Thread with tid %d was successfully created\n", tids[i]);
    }

    int status;
    for(int i = 0; i < 6; i++) { // will give an error on the last join
        status = thread_join(tids[i]);
        printf("Join status %d for thread %d\n", status, tids[i]);
    }

    thread_libterminate(); //this should mean when run with valgrind, no memory leaks

}