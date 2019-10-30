// Author: My Nguyen 
#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void f1(void*);
void f2(void*);
void f3(void*);

void f1(void *arg) {
  printf("Thread 1 here: I'm called first but I must wait til Thread 2 finishes\n");
  int t2 = thread_create(f2, NULL, 0);
  if (t2 == -1)
    exit(EXIT_FAILURE);
  if (thread_join(t2) == -1)
    exit(EXIT_FAILURE);
  printf("Thread 1: Now that Thread 2 finished, I can finish!\n");
}

void f2(void *arg) {
  printf("Thread 2: I'm here, but I must wait til Thread 3 finishes\n");
  int t3 = thread_create(f3, NULL, 0);
  if (t3 == -1)
    exit(EXIT_FAILURE);
  if (thread_join(t3) == -1)
    exit(EXIT_FAILURE);
  printf("Thread 2: Now that Thread 3 finished, I can finish!\n");
}
void f3(void *arg) {
  printf("Thread 3: No one's blocking me so I finish now!\n");
}

int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);
  
  printf("Test to demonstrate that join suspends calling thread until the joined one is finished\n");
  
  int t1 = thread_create(f1, NULL, 0);
  if (t1 == -1)
    exit(EXIT_FAILURE);
  if (thread_join(t1) == -1)
    exit(EXIT_FAILURE);
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);
  
  exit(EXIT_SUCCESS);
} 
