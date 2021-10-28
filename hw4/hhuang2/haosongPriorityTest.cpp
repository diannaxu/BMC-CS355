// Author Haosong Huang

// Author: Ziting Shen

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello_n1(void *arg) {
  for (int i = 0; i < 100;i++){
    poll(NULL, 0, 200);
    printf("%s -1\n", arg);
  }
}

void hello_0(void *arg) {
for (int i = 0; i < 100;i++){
    poll(NULL, 0, 200);
    printf("%s 0\n", arg);
  }}

void hello_1(void *arg) {
for (int i = 0; i < 100;i++){
    poll(NULL, 0, 200);
    printf("%s 1\n", arg);
  }}

int main(void) {
  if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  int tid_1 = thread_create(hello_n1, hello_str, -1);
  int tid_2 = thread_create(hello_0, hello_str, 0);
  int tid_3 = thread_create(hello_1, hello_str, 1);

  printf("Simplest test case for PRIORITY.\n");
  printf("Print \"Hello, world! <priority>\" for 300 times on success.\n");
  printf("Notice that the priority should repeat by 964 differently indicating different frequency\n");
  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);
  if (thread_join(tid_2) < 0) exit(EXIT_FAILURE);
  if (thread_join(tid_3) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
