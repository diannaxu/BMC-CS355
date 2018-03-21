#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void inner_most_foo(void *arg){
	thread_yield();
}

void inner_foo(void *arg){
    int tid = thread_create(inner_most_foo, NULL, 1);
    if (tid < 0){
      	exit(EXIT_FAILURE);
    }
    if (thread_join(tid) < 0){
      	exit(EXIT_FAILURE);
    }
}

void foo(void *arg){
  	for (int i = 0; i < 2; ++i){
    	int tid = thread_create(inner_foo, NULL, 1);
    	if (tid < 0){
      		exit(EXIT_FAILURE);
    	}
    	if (thread_join(tid) < 0){
      		exit(EXIT_FAILURE);
    	}
  	}
}

int main(){
	printf("** More complicated priority test, with three layers of nestedness. **\n");
	printf("** Upon success will print \"Exit success!!\"**\n");


	if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);
  

  int tid1 = thread_create(foo, NULL, 1);
  

  if (thread_join(tid1) < 0){
    exit(EXIT_FAILURE);
  }
  

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	
	exit(EXIT_SUCCESS);
}