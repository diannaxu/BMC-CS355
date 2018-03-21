#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo(void *arg){
	poll(NULL, 0, 200);
}

int main(){
	printf("** This is a basic priority test. **\n");
	printf("** Will create and join three threads. **\n");
	printf("** Each job will be scheduler 2 - 3 times (depending on how accurate the timer is) **\n");
	printf("** Upon success will print \"Exit success!!\"**\n");

	char *arg = "";
	int tid1, tid2, tid3;
	if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);

	tid1 = thread_create(foo, arg, -1);
	if (tid1 == -1) exit(EXIT_FAILURE);

	tid2 = thread_create(foo, arg, 0);
	if (tid2 == -1) exit(EXIT_FAILURE);

	tid3 = thread_create(foo, arg, 1);
	if (tid3 == -1) exit(EXIT_FAILURE);

	if (thread_join(1) == -1) exit(EXIT_FAILURE);

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	printf("Exit success!!\n");
	exit(EXIT_SUCCESS);
}