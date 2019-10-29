// INTERNAL_FUNCTION_NAME_SAFETY_TEST
// A test that uses functions and variables with the same names as
// internal functions and variables in userthread.c, to make sure
// there is no collision
// Expected behavior: the library is initialized, makes a "hello world" thread, and is terminated, once for each policy, without calling the function "schedule" defined in this file

#include <stdlib.h>
#include <stdio.h>
#include "userthread.h"

void schedule(){
  // Do the scheduling for my totally real work tasks i need to complete!
  printf("Function with same name as internal function is executing when it shouldn't be\n");
  exit(EXIT_FAILURE); 
}

void helloworld(){
  printf("Hello world\n");
  return; 
}

int main(){

  int tid1; 
  
  thread_libinit(FIFO);
  tid1 = thread_create(helloworld, NULL, 0);
  thread_join(tid1);
  thread_libterminate(); 

  thread_libinit(SJF);
  tid1 = thread_create(helloworld, NULL, 0);
  thread_join(tid1);
  thread_libterminate();

  thread_libinit(PRIORITY);
  tid1 = thread_create(helloworld, NULL, 0);
  thread_join(tid1);
  thread_libterminate();

  exit(EXIT_SUCCESS);
}
