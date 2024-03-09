//Testing priority to make sure functiosn end in the expected order

#include "userthread.h"
#include <time.h>

int arr[3] = {0};
int expected[3] = {1,2,3};
int count = 0;

void nanosleepwrap(struct timespec one, struct timespec two, int seconds){ // finish nano sleep kind of accurately.
        one.tv_sec = seconds;
        one.tv_nsec= 0; 
        int count = 0;
        int er = nanosleep(&one, &two);
        while(er == -1){
        count++;
        if (count % 2  == 1) er = nanosleep(&two,&one);
        else  er = nanosleep(&one, &two);

    }
    return ;
}

void f1(){   
    struct timespec sleepy;
    struct timespec rem;
    nanosleepwrap(sleepy,rem,5);
    printf("f1 finsihed\n");
    arr[count++] = 1; 

}
void f2(){
    struct timespec sleepy;
    struct timespec rem;
    nanosleepwrap(sleepy,rem,5);
    printf("f2 finsihed\n");
    arr[count++] = 2; 

}
void f3(){
    struct timespec sleepy;
    struct timespec rem;
    nanosleepwrap(sleepy,rem,5);
    arr[count++] = 3; 
    printf("f3 finsihed\n");
}

int main(){
    thread_libinit(PRIORITY);
    // tid_t tidList[2];
    // thread_create(f2,NULL,NULL); // 1
    thread_create(f3,NULL,LOW_PRIORITY); // 2
    thread_create(f1,NULL,HIGH_PRIORITY);// 3
    thread_create(f2,NULL,MID_PRIORITY);// 3

    thread_join(1);
    thread_join(2);
    thread_join(3);
    printf("second sleep\n");
 

    int count = 0;
    int er;
    thread_libterminate();
    for (int i = 0; i < 3; i++){
    if (arr[i] != expected[i]){
        printf("Unexpected order");
        return EXIT_FAILURE;
        }
    }
    printf("SUCCESS"); 
    return EXIT_SUCCESS;
}