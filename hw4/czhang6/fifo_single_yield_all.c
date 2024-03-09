/**
 * test 3 - fifo with single yield
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks FIFO scheduling with single call of thread yield. Creates 2  
 *              threads to run a func that prints 2 lines, call yield between the prints. 
 * 
 * Expected output: 
 * 
 * test 3
 * task 1: 1 out of 2 done
 * task 2: 1 out of 2 done
 * task 1: 2 out of 2 done!!
 * task 2: 2 out of 2 done!!
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int id = *(int *)arg;
    printf("task %d: 1 out of 2 done\n", id);
    thread_yield();
    printf("task %d: 2 out of 2 done!!\n", id);
}

int main() {
    if (thread_libinit(FIFO) == -1){
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 3\n");

    int task_num1 = 1;
    int task_num2 = 2;

    int tid1 = thread_create(task, &task_num1, 0);
    int tid2 = thread_create(task, &task_num2, 0);

    if (tid1 == -1 || tid2 == -1) {
        printf("Can't create thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1) {
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
