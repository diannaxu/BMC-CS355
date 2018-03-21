#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo1(void *arg){
	for (int i = 0; i < 5; i++) {
    poll(NULL, 0, 150);
    thread_yield();
  }
}

void foo2(void *arg){
	for (int i = 0; i < 5; i++) {
    poll(NULL, 0, 1);
    thread_yield();
  }
}

void foo3(void *arg){
	for (int i = 0; i < 5; i++) {
    poll(NULL, 0, 300);
    thread_yield();
  }
}

int main(){
	printf("** This is a basic sjf test. **\n");
	printf("** Will create and join three threads. **\n");
	printf("** Upon success will print \"Exit success!!\"**\n");
	

	char *arg = "";
	int tid1, tid2, tid3;
	if (thread_libinit(SJF) == -1) exit(EXIT_FAILURE);

	tid1 = thread_create(foo1, arg, 1);
	if (tid1 == -1) exit(EXIT_FAILURE);

	tid2 = thread_create(foo2, arg, 1);
	if (tid2 == -1) exit(EXIT_FAILURE);

	tid3 = thread_create(foo3, arg, 1);
	if (tid3 == -1) exit(EXIT_FAILURE);

	printf(" * The threads should end in the order %d -> %d -> %d \n",
          tid2, tid1, tid3);

	if (thread_join(tid1) == -1) exit(EXIT_FAILURE);

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	printf("Exit Success!!\n");
	exit(EXIT_SUCCESS);
}