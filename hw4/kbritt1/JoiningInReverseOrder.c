//Joining in reverse
#define NO_PRIORITY -1
#define NUM_THREADS 50
#include "userthread.h"


void f1(){
}
int main(){
    thread_libinit(FCFS);
    tid_t thread_array[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++){
        thread_array[i] = thread_create(f1,NULL,NO_PRIORITY);
    }
    for(int i = NUM_THREADS-1; i >= 0 ;i--){
        thread_join(thread_array[i]);
    }
    thread_libterminate();

    printf("SUCCESS\n");
    return EXIT_SUCCESS;
}