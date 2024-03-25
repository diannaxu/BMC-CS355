/**
 * test 9 - basic test for SJF
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks SJF scheduling with 3 threads. Creates 3 threads 
 *              to print a line with thread id, then join and terminates the lib.  
 * 
 * Expected output: 
 * 
 * test 9
 * 1: Hello, New York City!
 * 2: Hello, New York City!
 * 3: Hello, New York City!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("%d: Hello, New York City!\n", id); // I really wrote this test in NYC!!
}

int main() {
    if (thread_libinit(SJF) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    }

    printf("test 9\n");

    int task_1 = 1;
    int task_2 = 2;
    int task_3 = 3;

    int tid1 = thread_create(task, &task_1, 0);
    int tid2 = thread_create(task, &task_2, 0);
    int tid3 = thread_create(task, &task_3, 0);

    if (tid1 == -1 || tid2 == -1 || tid3 == -1) {
        printf("Can't create threads\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1 || thread_join(tid3) == -1) {
        printf("Can't join on threads\n");
        exit(EXIT_FAILURE);
    }

    printf("done\n");

    if (thread_libterminate() == -1) {
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
