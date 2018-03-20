#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void child(void* nothing) {
  printf("Ops, I am a child, not thread created.\n");

}

void test(void* trash) {
  printf("Ha! We create a new thread!\n");
  int tid = thread_create(child,NULL,0);

  thread_join(tid);
}
/*
  a simple basic fifo test.
  You can also comment all the thread_create and thread_join
  to test whether your thread_libinit and thread_libterminate works
*/

int main(int args, char** argv) {
  if(thread_libinit(FIFO) == 0)
    printf("Ya ho!\n");
  else
    printf("Sad.. I fail\n");
  
  printf("We should have four threads in total. They should be ended in order 3 -> 4 -> 1 -> 2\n"); 
  int tid1 =  thread_create(test,NULL,0);
  int tid2 =  thread_create(test,NULL,0);
  /*
  mythread* tmp; //= fifoq.front();
  //fifoq.push(tmp);
  fifoq.pop();
  tmp = fifoq.front(); // this should be test
  setcontext(tmp->uc);
  */
  //thread_yield();
  thread_join(tid1);
  //cout << "size of queue is now: " << fifoq.size() << endl;
  if(thread_libterminate() == 0)
    printf("lib term Ya ho!\n");
  else
    printf("Sad.. I fail to term\n");

  //mythread* kk = fifoq.front();
  //makecontext(kk->uc, test, 0);
  //setcontext(kk->uc);
  return 0;
}