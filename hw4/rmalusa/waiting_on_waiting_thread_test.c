// WAITING_ON_WAITING_THREAD_TEST.C
// Author: Ruby Malusa
// Makes sure that the library behaves correctly
// when a thread does a join on a thread that is already wating on a join 
// Expected behavior: first thread yields, second thread waits on it, third thread waits on second thread, main waits on third thread... then first thread runs, freeing second thread, which frees third, which frees main, which terminates

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int tid1;
int tid2;
int tid3; 

void thread1(void* args){
  thread_yield(); 
}

void thread2(void* args){
  thread_join(tid1); 
}

void thread3(void* args){
  thread_join(tid2); 
}

int main(){
  thread_libinit(FIFO); 
  tid1 = thread_create(thread1, NULL, 0);
  tid2 = thread_create(thread2, NULL, 0);
  tid3 = thread_create(thread3, NULL, 0); 
  thread_join(tid3); 
  thread_libterminate(); 
}
