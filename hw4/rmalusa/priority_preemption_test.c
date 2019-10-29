// PRIORITY_PREEMPTION_TEST.C
// Author: Ruby Malusa
// Tests that jobs that run for longer than the 100ms quantum are preempted
// Expected behavior: scheduler log shows that each job only gets to run for 100ms, (unless they've done four polls already, in which case they finish immediately)

#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include "userthread.h"

void long_job(void* args){
  for(int i=0; i<5; i++){
    poll(NULL, 0, 200); 
  }
}

int main(){
  thread_libinit(PRIORITY);

  int tid1 = thread_create(long_job, NULL, -1);
  int tid2 = thread_create(long_job, NULL, 0);
  int tid3 = thread_create(long_job, NULL, 1); 

  thread_join(tid1);
  thread_join(tid2);
  thread_join(tid3);
  
  thread_libterminate();
  exit(EXIT_SUCCESS); 
}
