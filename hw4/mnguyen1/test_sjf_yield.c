// Author: My Nguyen
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
#include <poll.h>
#include <unistd.h>

void f1(void* arg) {
  for (int i = 0; i < 3; i++) {
    printf("Thread 1 here!\n");
    poll(NULL, 0, 100);
    thread_yield();
  }
}

void f2(void* arg) {
  for (int i = 0; i < 3; i++) {
    printf("Thread 2 here!\n");
    poll(NULL, 0, 300);
    thread_yield();
  }
}

void f3(void* arg) {
  for (int i = 0; i < 3; i++) {
    printf("Thread 3 here!\n");
    poll(NULL, 0, 200);
    thread_yield();
  }
}

int main(void) {
  if (thread_libinit(SJF) == -1)
    exit(EXIT_FAILURE);
  
  printf("Test to demonstrate sjf working with yield\n");
  printf("Should print in order 1 2 3 1 1 3 3 2 2\n");
  
  int t1 = thread_create(f1, NULL, -1);
  int t2 = thread_create(f2, NULL, -1);
  int t3 = thread_create(f3, NULL, -1);
  int tids[] = { t1, t2, t3 };
  
  for (int i = 0; i < 3; i++) {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < 3; i++) {
    if (thread_join(tids[i]) == -1)
      exit(EXIT_FAILURE);
  }
  
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);
  
  exit(EXIT_SUCCESS);
} 

