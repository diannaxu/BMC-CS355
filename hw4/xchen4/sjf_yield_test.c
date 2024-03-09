// Author: Paprika Chen
// Test if the estimated time for jobs are correct
// Right behavior: short task ends before long task ends

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include "userthread.h"

void short_task(void* args) {
  for (int i = 0; i < 2; i++) {
    sleep(1); // Simulate a shorter task with sleep
    thread_yield();
  }
  printf("Short task, expected to end first\n");
}

void long_task(void* args) {
  for (int i = 0; i < 2; i++) {
    sleep(2); // Simulate a longer task with sleep
    thread_yield();
  }
  printf("Long task, expected to end last\n");
}

int main() {
  if (thread_libinit(SJF) == -1) {
    printf("Failed to initialize thread library\n");
    exit(EXIT_FAILURE);
  }

  int tid_short = thread_create(short_task, NULL, 0);
  int tid_long = thread_create(long_task, NULL, 0);

  if (tid_short == -1 || tid_long == -1) {
    printf("Failed to create a thread\n");
    thread_libterminate();
    exit(EXIT_FAILURE);
  }

  if (thread_join(tid_short) == -1 || thread_join(tid_long) == -1) {
    printf("Failed to join a thread\n");
    thread_libterminate();
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1) {
    printf("Failed to terminate thread library\n");
    exit(EXIT_FAILURE);
  }

  printf("SJF scheduling test with sleep() completed successfully.\n");

  exit(EXIT_SUCCESS);
}