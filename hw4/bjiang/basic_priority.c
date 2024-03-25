//Author: Ben Jiang
//This is a basic test for the priority policy with one thread in each priority
//Should be able to access and run all threads in all the 3 queues without errors

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

struct timespec ts1,ts2;

void test1(){
    nanosleep(&ts1,NULL);
    printf("In test1\n");
}

void test2(){
    nanosleep(&ts1,NULL);
    printf("In test2\n");
}

void test3(){
    nanosleep(&ts1,NULL);
    printf("In test3\n");
}

int main(){
    thread_libinit(PRIORITY);
    ts1.tv_nsec = 1000;
    ts1.tv_sec = 0;
    tid_t tid1 = thread_create(test1,NULL,HIGHPRIORITY);
    tid_t tid2 = thread_create(test2,NULL,MIDPRIORITY);
    tid_t tid3 = thread_create(test3,NULL,LOWPRIORITY);
    if(tid1 == -1 || tid2 == -1 || tid3 == -1){
        return EXIT_FAILURE;
    }

    int a = thread_join(tid1);
    int b = thread_join(tid2);
    int c = thread_join(tid3);

    if(a == -1 || b == -1 || c == -1){
        return EXIT_FAILURE;
    }

    printf("Returned to main\n");
    if(-1 == thread_libterminate()){
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}