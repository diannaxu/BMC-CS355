/**
 * test 4 - fifo yielding with only one thread
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks FIFO scheduling with yielding when there only exists one thread. 
 *              ONLY 1 thread created, calls yield in the middle of thread fn, nothing should happen. 
 * 
 * Expected output: 
 * 
 * test 4
 * task 1: 1 out of 2 done
 * task 1: 2 out of 2 done!!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("task %d: 1 out of 2 done\n", id);
    if (id == 1){
        thread_yield();
    }
    printf("task %d: 2 out of 2 done!!\n", id);
}

int main() {
    if (thread_libinit(FIFO) == -1){
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 4\n");

    int task_num = 1;

    int tid = thread_create(task, &task_num, 0);

    if (tid == -1) {
        printf("Can't create thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid) == -1) {
        printf("Can't join thread\n");
        exit(EXIT_FAILURE);
    }

    printf("done\n");

    if (thread_libterminate() == -1){
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
