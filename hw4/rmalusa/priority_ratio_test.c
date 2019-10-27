// PRIORITY_RATIO_TEST.C
// Repeats many times the process of 1) creating a low and medium priority thread and 2) seeing which one finishes first.
// This allows us to measure the ratio in which low and medium-priority threads are scheduled. 

#include <stdlib.h>
#include <stdio.h>
#include "userthread.h"

#define ERROR -1 
#define LOW 1
#define MEDIUM 0 

int whos_on_last; 

void lowpriority(){
  whos_on_last = LOW; 
}

void mediumpriority(){
  whos_on_last = MEDIUM; 
}
  
int main(){
  int status = thread_libinit(PRIORITY);
  if(status == ERROR){
    printf("Could not initialize library\n");
    exit(1); 
  }
  
  int low_finished_first = 0;
  int medium_finished_first = 0; 

  for(int i=0; i<1000; i++){
    int tid1 = thread_create(lowpriority, NULL, 1);
    if(tid1 == ERROR){
      printf("Could not create thread\n");
      exit(1); 
    }
    int tid2 = thread_create(mediumpriority, NULL, 0);
    if (tid2 == ERROR){
      printf("Could not create thread\n");
      exit(1); 
    }
    
    status = thread_join(tid1);
    if(status == ERROR){
      printf("Error joining thread\n"); 
    }
    status = thread_join(tid2);
    if(status == ERROR){
      printf("Error joining thread\n"); 
    }
    if(whos_on_last == LOW){
      medium_finished_first++; 
    } else {
      low_finished_first++; 
    }			 
  }
  printf("Ratio of low to medium priority threads terminating first: %d:%d\n", low_finished_first, medium_finished_first); 
  printf("Should be approximately 333/666\n"); 
  status = thread_libterminate();
  if(status == ERROR){
    printf("Error terminating library\n");
    exit(1); 
  }
  exit(0); 
}
