/*
author: Yue Chen
The program is to test thread_yield when there is only one thread in queue
*/
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

void a(){
    printf("Thread A is working\n");
    printf("Thread A yielding\n");
    thread_yield();
    printf("Continuing Thread A\n");
    printf("Thread A done\n");
}

int main(){
    if(thread_libinit(FIFO)==0){
        printf("FIFO Scheduling\n");
    }else{
        printf("Failed to Schedule\n");
        exit(EXIT_FAILURE);
    }
    int tid_a = thread_create(a,NULL,0);
    if(thread_join(tid_a)!=0){
        printf("Failed to join Thread A\n");
    }
    if(thread_libterminate()!=0){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}