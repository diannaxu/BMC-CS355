/**
 * test 10 - SJF with yielding
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks SJF scheduling with 3 threads, where each thread will yield once. 
 *              Creates 3 threads to print 2 lines, then calls yield, and print the last 
 *              line (finish).  
 *              
 * Expected output: 
 * 
 * test 10
 * 1: started
 * 1: working
 * 2: started
 * 2: working
 * 3: started
 * 3: working
 * 1: finished!
 * 2: finished!
 * 3: finished!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("%d: started\n", id);
    printf("%d: working\n", id);
    thread_yield(); 
    printf("%d: finished!\n", id);
}

int main() {
    if (thread_libinit(SJF) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    }

    printf("test 10\n");

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
