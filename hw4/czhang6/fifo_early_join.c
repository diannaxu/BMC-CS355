/**
 * test 8 - fifo early join
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks FIFO scheduling with early join on the first 2 threads, but not the last thread. 
 *              Creates 3 threads to print some lines, call join on threads 1 and 2, but no join for thread 3. 
 *              Main also prints when join is done. 
 * 
 * Expected output: 
 * 
 * test 8
 * 1: started
 * 1: working
 * 1: finished!
 * 2: started
 * 2: working
 * 2: finished!
 * main: join done. No join for thread 3. 
 * 3: started
 * 3: working
 * 3: finished!
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("%d: started\n", id);
    printf("%d: working\n", id);
    printf("%d: finished!\n", id);
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    }

    printf("test 8\n");
    
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

    // join on thread 1 and 2 but not 3
    if (thread_join(tid1) == -1 || thread_join(tid2) == -1) {
        printf("Can't join on thread 1 or 2\n");
        exit(EXIT_FAILURE);
    }

    printf("main: join done. No join for thread 3. \n");

    if (thread_libterminate() == -1) {
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
