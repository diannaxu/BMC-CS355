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
	printf("** This is a nested fifo test. **\n");
	printf("** Upon success will print \"Exit success!!\"**\n");

	if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);


  	int tid1 = thread_create(foo, NULL, 1);

  	printf("More complicated FIFO test, with three layers of nestedness.\n");
  	printf("Assuming that the first thread is tid 1, it should finish in order\n");
  	printf("3 -> 2 -> 5 -> 4 -> 1\n");

  	if (thread_join(tid1) < 0){
    	exit(EXIT_FAILURE);
  	}

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	printf("Exit success!!\n");
	exit(EXIT_SUCCESS);
}