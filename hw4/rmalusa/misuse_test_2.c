// MISUSE_TEST_2.c
// Tests that the library reacts reasonably when the user tries to 1) create and join threads before initializing it and 2) join an invalid TID 
// Expected behavior: return -1 for each operation, causing the error messages to print; no segfaults/memory leaks 

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define ERROR -1 

void blank(void* args){}

int main(){

  // Thread creation without initializing library 
  int tid = thread_create(blank, NULL, 0);
  if(tid == ERROR){
    printf("Thread could not be created\n");
  }

  // Thread joining without initializing library 
  int status = thread_join(tid);
  if(status == ERROR){
    printf("Thread could not be joined\n");
  }

  // Initialize library 
  thread_libinit(FIFO);

  // Thread joining with an invalid TID
  status = thread_join(ERROR);
  if(status == ERROR){
    printf("Thread could not be joined\n"); 
  }

  thread_libterminate(); 
}
