// Author: Ben Jiang

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define THREAD_NUMBER 100
#define FAIL -1

void dummy(void *arg)
{
    while(rand() % 10 != 0){
        printf("1\n");
    }

}

void dummy1(void *arg){
    while(rand() % 10 != 0){
        printf("2\n");
    }
}

void dummy2(void *arg){
    while(rand() % 10 != 0){
        printf("3\n");
    }
}

int main(void)
{
    thread_libinit(PRIORITY);
    srand(time(NULL));

    tid_t tid1,tid2,tid3;
    tid1 = thread_create(dummy,NULL,-1);
    tid2 = thread_create(dummy1,NULL,0);
    tid3 = thread_create(dummy2,NULL,1);
    if(thread_join(tid1) == FAIL){
        exit(EXIT_FAILURE);
    }
    if(thread_join(tid2) == FAIL){
        exit(EXIT_FAILURE);
    }
    if(thread_join(tid3) == FAIL){
        exit(EXIT_FAILURE);
    }

    if(FAIL == thread_libterminate()){
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
