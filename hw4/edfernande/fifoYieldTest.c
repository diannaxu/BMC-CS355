// Elly Fernández

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "userthread.h"

/* A fifo test of thread create, join, and yield. Three threads are created.
* Thread 1 prints out odd numbers between 1 and 9, yielding at 3 to Threads 2 and
* 3 who print out even numbers between 2 and 8. Once the program is done, should
* return to main and print "All done :)"
*
* Expected output:
Thread with tid 1 with create status: 0
Thread with tid 2 with create status: 0
1
3
0
2
4
6
8
0
2
4
6
8
5
7
9
All done :)
*/

int tids[3];
int currThread;

void countsToTenY(void* arg) {
    for(int i = 1; i < 10; i+=2) {
        printf("%d\n", i);
        sleep(1);
        if(i == 3) {
            //thread_join(2);
            thread_yield();
        }
    }
    return;
}

void countsToTen(void* arg) {
    for(int i = 0; i < 10; i+=2) {
        printf("%d\n", i);
        sleep(1);
    }
}

int main(int argc, char** argv) {
    int initStatus = thread_libinit(FIFO);
    if(initStatus == -1) {
        exit(EXIT_FAILURE);
    }

    int createStatus = thread_create(countsToTenY, NULL, 0);
    tids[0] = 1;
    for(int i = 1; i < 3; i++) {
        int createStatus = thread_create(countsToTen, NULL, 0);
        tids[i] = i+1;
        printf("Thread with tid %d with create status: %d\n", i, createStatus);
    }

    currThread = 1;
    int status = thread_join(currThread);

    printf("All done :)\n");

    thread_libterminate();
    exit(EXIT_SUCCESS);
}
