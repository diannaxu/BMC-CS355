/**
 * test 6 - fifo with miltiple yields in all threads
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks FIFO scheduling with multiple calls of yield in all threads. 
 *              Creates 2 threads to run a func with 3 printf(), call yield between all printf(). 
 * 
 * Expected output: 
 * 
 * test 6
 * task 1: 1 out of 3 done
 * task 2: 1 out of 3 done
 * task 1: 2 out of 3 done
 * task 2: 2 out of 3 done
 * task 1: 3 out of 3 done!!
 * task 2: 3 out of 3 done!!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("task %d: 1 out of 3 done\n", id);
    thread_yield();

    printf("task %d: 2 out of 3 done\n", id);
    thread_yield();

    printf("task %d: 3 out of 3 done!!\n", id);
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 6\n"); 

    int id1 = 1;
    int id2 = 2;

    int tid1 = thread_create(task, &id1, 0);
    int tid2 = thread_create(task, &id2, 0);

    if (tid1 == -1 || tid2 == -1) {
        printf("Can't create thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1) {
        printf("Can't join thread\n");
        exit(EXIT_FAILURE);
    }

    printf("done\n");

    if (thread_libterminate() == -1) {
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
