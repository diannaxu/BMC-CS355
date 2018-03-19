#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello_100(void *arg) {
	poll(NULL, 0, 100);
	thread_yield();
	poll(NULL, 0, 100);
	thread_yield();
	poll(NULL, 0, 100);
	thread_yield();
	printf("%s 100\n", arg);
}

void hello_150(void *arg) {
	poll(NULL, 0, 150);
	thread_yield();
	poll(NULL, 0, 150);
	thread_yield();
	poll(NULL, 0, 150);
	thread_yield();
	printf("%s 150\n", arg);
}

void hello_200(void *arg) {
	poll(NULL, 0, 200);
	thread_yield();
	poll(NULL, 0, 200);
	thread_yield();
	poll(NULL, 0, 200);
	thread_yield();
	printf("%s 200\n", arg);
}

int main(void) {
	if (thread_libinit(SJF) == -1) exit(EXIT_FAILURE);

	char *hello_str = "Hello, world!";
	int tid_1 = thread_create(hello_100, hello_str, 0);
	int tid_2 = thread_create(hello_150, hello_str, 0);
	int tid_3 = thread_create(hello_200, hello_str, 0);

	printf("Test case for SJF.\n");
	printf("Print \"Hello, world! 100\", \"Hello, world! 150\", \"Hello, world! 200\" on success.\n");
	printf("The order cannot be inverted.\n");

	if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);
	if (thread_join(tid_2) < 0) exit(EXIT_FAILURE);
	if (thread_join(tid_3) < 0) exit(EXIT_FAILURE);

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}