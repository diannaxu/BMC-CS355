// Author: Ruby Malusa
// MISUSE_TEST_2.C
// Tests that the library reacts reasonably to things a user might do that are wrong, like performing thread operations without initializing the library, initializing the library twice without terminating it in between, and terminating the library twice

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define ERROR -1 

void blank(void* args){}

int main(){

  // Thread creation without initializing library 
  int tid = thread_create(blank, NULL, 0);
  if(tid == ERROR){
    printf("Thread could not be created (expected: library not initialized)\n");
  }

  // Thread joining without initializing library 
  int status = thread_join(tid);
  if(status == ERROR){
    printf("Thread could not be joined (expected: library not initialized)\n");
  }

  // Initialize library 
  status = thread_libinit(FIFO);
  if(status == ERROR){
    printf("Library could not be initialized\n");
    exit(EXIT_FAILURE); 
  }
  
  // Initialize library a second time
  status = thread_libinit(SJF); 
  if(status == ERROR){
    printf("Library could not be initialized (expected: library already initialized)\n"); 
  }
  
  // Thread joining with an invalid TID
  status = thread_join(ERROR);
  if(status == ERROR){
    printf("Thread could not be joined (expected: TID invalid)\n"); 
  }

  status = thread_libterminate();
  if(status == ERROR){
    printf("Library could not be terminated\n");
    exit(EXIT_FAILURE); 
  }
  
  status = thread_libterminate();
  if(status == ERROR){
    printf("Library could not be terminated (expected: already terminated)\n");
  }
  exit(EXIT_SUCCESS);
}
