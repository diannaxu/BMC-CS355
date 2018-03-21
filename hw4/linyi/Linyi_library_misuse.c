#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo(void *arg){
	poll(NULL, 0, 200);
}

int main(){
	printf("** This is a test for misuse. **\n");
	printf("** Should not crash or have memory leak **\n");
	printf("** Upon successful exit will print \"Exit success!!\"**\n");

	char *arg = "";
	if (thread_libinit(1000000) != -1) exit(EXIT_FAILURE); //invalid policy

	//invalid create without initialization
	if (thread_create(foo, arg, -1) != -1) exit(EXIT_FAILURE);

	//invalid create without initizlization
	if (thread_join(1)!= -1) exit(EXIT_FAILURE);

	printf("Exit success!!\n");
	exit(EXIT_SUCCESS);
}