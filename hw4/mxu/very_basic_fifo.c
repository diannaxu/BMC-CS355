#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


void test(void* trash) {
  printf("hello, world\n");
}
/*
  a very simple basic fifo test.
  You can also comment all the thread_create and thread_join
  to test whether your thread_libinit and thread_libterminate works
*/

int main(int args, char** argv) {
  if(thread_libinit(FIFO) == 0)
    printf("Ya ho!\n");
  else
    printf("Sad.. I fail\n");
  
  printf("thread 1 should ends more early than thread 2."); 
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