//Author: Ben Jiang
//Basic test for FIFO, SJF, and Priority. Contains 3 dummy functions each 
//Should not return any errors or cause any segfault/memory error
#define FAIL -1
#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"
#include <time.h>

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


int main(){ //only for testing
    thread_libinit(FCFS);

    tid_t tidList[3];
    for(int i = 0; i < 3; i++){
        tidList[i] = thread_create(test1,NULL,NO_PRIORITY);
    }
    for(int i = 2; i >= 0; i--){
        thread_join(tidList[i]);
    }

    thread_yield();
    printf("Returned to main\n");
    if(FAIL == thread_libterminate()){
        exit(EXIT_FAILURE);
    }

    thread_libinit(SJF);
    tid_t tid1 = thread_create(test1,NULL,NO_PRIORITY);
    tid_t tid2 = thread_create(test2,NULL,NO_PRIORITY);
    tid_t tid3 = thread_create(test3,NULL,NO_PRIORITY);
    thread_join(tid1);
    thread_join(tid2);
    thread_join(tid3);
    tid3 = thread_create(test3,NULL,NO_PRIORITY);
    tid2 = thread_create(test2,NULL,NO_PRIORITY);
    tid1 = thread_create(test1,NULL,NO_PRIORITY);
    
    printf("Back to main\n");
    if(FAIL == thread_libterminate()){
        exit(EXIT_FAILURE);
    }
    
    //needs to test yield
    thread_libinit(PRIORITY);
    ts1.tv_nsec = 1000000;
    ts1.tv_sec = 0;
     tid1 = thread_create(test1,NULL,HIGHPRIORITY);
     tid2 = thread_create(test2,NULL,MIDPRIORITY);
     tid3 = thread_create(test3,NULL,LOWPRIORITY);
 
    thread_join(tid1);
    thread_join(tid2);
    thread_join(tid3);
    printf("Returned to main\n");
    if(FAIL == thread_libterminate()){
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}