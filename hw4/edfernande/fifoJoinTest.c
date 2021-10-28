//Elly Fernández
#include <stdio.h>
#include <stdlib.h>
#include "userthread.c"
#define THREAD_NUM 6

/* This program creates 6 threads. It has thread 1 wait for thread 3, thread 2 wait
* for thread 4, and thread 3 wait for 6. When each thread runs, it will print out
* its id as given above. 
* FIFO expected output:
* Started running thread 1
* Started running thread 2
* Started running thread 3
* Started running thread 4
* Finished running thread 4
* Started running thread 5
* Finished running thred 5
* Started running thread 6
* Finished running thread 6
* Returned to main
*/

typedef struct {
    int threadNum;
    int waitFor;
} PassInfo;

void joinTest(void* info) {
    PassInfo* threadData = info;
    printf("Started running thread %d\n", threadData->threadNum);
    if(threadData->waitFor != -1) {
        thread_join(threadData->waitFor);
    }
    printf("Finished Running thread %d\n", threadData->threadNum);
}

int main(int argc, char** argv) {
    PassInfo threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++) {
        threads[i].threadNum = i+1;
        threads[i].waitFor = -1;
    }
    threads[0].waitFor = 3;
    threads[2].waitFor = 4;
    threads[3].waitFor = 6;

    thread_libinit(FIFO);

    for(int i = 0; i < THREAD_NUM; i++) {
        thread_create(joinTest, &threads[i], 0);
    }
    
    thread_join(1);
    printf("Returned to main\n");
    thread_libterminate();
}
