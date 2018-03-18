
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h>
#include <poll.h>


void printArg(){
  printf("arg\n");
}


int testLl(){
	thread_libinit(SJF); // FIFO SJF PRIORITY

	//create
	int tid1 = thread_create(printArg, NULL, 0);
	int tid2 = thread_create(printArg, NULL, -1);


	// join
	thread_join(tid1);
	thread_join(tid2);
	
	int tid3 = thread_create(printArg, NULL, 1);
	
	thread_join(tid3);


	// term
	thread_libterminate();

	return 1;
}


int main(){
  testLl();
  return 1;
}
