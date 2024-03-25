/*
author: Yue Chen
The program is to test Priority scheduling with different priority while do yielding
The sequence is random, content at userthread_log.txt is more important
*/
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void a() {
  poll(NULL, 0, 250);
  thread_yield();
  printf("Thread A done\n");
}

void b() {
  poll(NULL, 0, 250);
  thread_yield();
  printf("Thread B done\n");
}

void c() {
  poll(NULL, 0, 200);
  thread_yield();
  printf("Thread C done\n");
}

int main(){
    if(thread_libinit(PRIORITY)==0){
        printf("Priority Scheduling\n");
    }else{
        printf("Failed to Schedule\n");
        exit(EXIT_FAILURE);
    }
    int tid_a = thread_create(a,NULL,1);
    int tid_b = thread_create(b,NULL,0);
    int tid_c = thread_create(c,NULL,-1);
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
