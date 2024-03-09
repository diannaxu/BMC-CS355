/*
author: Yue Chen
The program is to test FIFO scheduling
*/
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

void a(){
    printf("Thread A is working\n");
    printf("Thread A done, should be first\n");
}
void b(){
    printf("Thread B is working\n");
    printf("Thread B done, should be second\n");
}
void c(){
    printf("Thread C is working\n");
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
    if(thread_join(tid_a)!=0){
        printf("Failed to join Thread A\n");
    }
    if(thread_join(tid_b)!=0){
        printf("Failed to join Thread B\n");
    }
    if(thread_join(tid_c)!=0){
        printf("Failed to join Thread C\n");
    }
    if(thread_libterminate()!=0){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}