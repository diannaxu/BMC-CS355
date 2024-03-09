/*
author: Yue Chen
The program is to test thread_join with a bad ID
*/
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

void a(){
    printf("Thread A done, should be first\n");
}
void b(){
    printf("Thread B done, should be second\n");
}
void c(){
    printf("Thread C done, should be third\n");
}
int main(){
    if(thread_libinit(FIFO)==0){
        printf("FIFO Scheduling\n");
    }else{
        printf("Failed to Schedule\n");
        exit(EXIT_FAILURE);
    }
    int tid_a = thread_create(a,NULL,0);
    int tid_b = thread_create(b,NULL,0);
    int tid_c = thread_create(c,NULL,0);
    if(thread_join(4)!=0){
        printf("Failed to join Thread 4\n");
    }
    if(thread_libterminate()!=0){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}