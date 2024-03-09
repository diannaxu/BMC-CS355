/*
author: Yue Chen
The program is to test threadtable size limit

Good Behavior: 
FIFO Scheduling
Failed to create new thread 
Created a new thread
*/
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#define size 512

void a(){
}
void b(){
    printf("Created a new thread\n");
}

int main(){
    if(thread_libinit(FIFO)==0){
        printf("FIFO Scheduling\n");
    }else{
        printf("Failed to Schedule\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<size;i++){
        if(thread_create(a,NULL,0)==-1){
            exit(EXIT_FAILURE);
        }
    }
    // Test if thread table is full
    if(thread_create(b,NULL,0)==-1){
        printf("Failed to create new thread \n");
    }
    for(int i=0;i<size;i++){
        if(thread_join(i)==-1){
            printf("failed to join thread %d\n",i);
        }
    }
    if(thread_create(b,NULL,0)==-1){
        printf("Failed to create new thread \n");
    }
    // Test if new thread is assigned tid 0
    if(thread_join(0)==-1){
        printf("failed to join thread\n");
    }
    if(thread_libterminate()!=0){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}