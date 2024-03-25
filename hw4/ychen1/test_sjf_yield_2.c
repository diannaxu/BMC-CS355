/*
author: Yue Chen
The program is to test SJF scheduling and thread_yield in the case of SJF
*/
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h> 
#include "userthread.h"

void A() {
    sleep(1);
    thread_yield();
    printf("Thread A done, should be second\n");
}

void B() {
    sleep(2);
    thread_yield();
    printf("Thread B done, should be third \n");
}

void C() {
    thread_yield();
    printf("Thread C done, should be first \n");
}

int main(void) {
  if (thread_libinit(SJF) == -1)
    exit(EXIT_FAILURE);

  int tidA = thread_create(A, NULL, 0);
  int tidB = thread_create(B, NULL, 0);
  int tidC = thread_create(C, NULL, 0);

  int n  = 3;
  int tids[] = { tidA, tidB, tidC };

  for (int i = 0; i < n; i++)  {
    if (thread_join(tids[i]) == -1){
      printf("Failed to join");
    }
  }

    if(thread_libterminate() == -1){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}