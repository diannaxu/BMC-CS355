//testing FCFS insertion

#define NO_PRIORITY -1
#include "userthread.h"
int count = 0;
int arr[3] = {0};
int expected[3] = {2,3,1};
void f1(){
    arr[count++] = 1;
}
void f2(){
    arr[count++] = 2;
}
void f3(){
    arr[count++] = 3;
}


int main(){
    thread_libinit(FCFS);
    tid_t one = thread_create(f2,NULL,NO_PRIORITY); // 1
    tid_t two = thread_create(f3,NULL,NO_PRIORITY); // 2
    tid_t three=  thread_create(f1,NULL,NO_PRIORITY);// 3
    thread_join(one);
    thread_join(two);
    thread_join(three);

    thread_libterminate();
    for (int i = 0; i < 3; i++){
        if (arr[i] != expected[i]){
            printf("Unexpected order\n");
            return EXIT_FAILURE;
        }

    }
    printf("SUCCESS\n");
    return EXIT_SUCCESS;
}