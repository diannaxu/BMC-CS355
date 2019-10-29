// AUTHOR: Ruby Malusa
// EARLY_TERMINATION_TEST.C
// A very simple test to ensure the library behaves reasonably
// and correctly frees all its memory if the library is terminated before all threads have completed.
// The second part of the test engineers a situation where a thread is waiting/hung off another thread when the library is terminated. 
//Expected output: no memory leaks!


#include <stdlib.h>
#include <stdio.h>
#include "userthread.h"

int tid; 

void blank(void* args){}

void yield(void* args){
  thread_yield(); 
}

void wait_on_thread(void* args){
  thread_join(tid);
}

int main(){
  thread_libinit(FIFO);
  for(int i=0; i<10; i++){
    thread_create(blank, NULL, 0);
  }
  thread_libterminate();

  thread_libinit(FIFO);
  int tid1 = thread_create(blank, NULL, 0); 
  thread_create(wait_on_thread, NULL, 0); 
  tid = thread_create(yield, NULL, 0);
  thread_join(tid1); 
  thread_libterminate(); 
  exit(EXIT_SUCCESS);
}
