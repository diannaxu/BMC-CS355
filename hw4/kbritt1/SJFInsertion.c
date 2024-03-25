// TEST SJF inserition, making sure SJF insertion is correct after collect time for each function f1,f2,f3
#include "userthread.h"

int expected[] = {1,2,3};
int arr[3];
int count; 
void f1(){
    if (count < 3) count++;
    else arr[count++-3] = 1;
    printf("hello\n");
    
}
void f2(){
    if (count < 3) count++;
    else arr[count++-3] = 2;
    sleep(2);
}
void f3(){
    if (count < 3) count++;
    else arr[count++-3] = 3;
    sleep(3);
}

int main(){
    thread_libinit(SJF);
    tid_t one = thread_create(f2,NULL,NO_PRIORITY); // 1
    tid_t two = thread_create(f3,NULL,NO_PRIORITY); // 2
    tid_t three = thread_create(f1,NULL,NO_PRIORITY);// 3
    thread_join(one);
    thread_join(two);
    thread_join(three);
    tid_t four = thread_create(f3,NULL,NO_PRIORITY); // 4
    tid_t five = thread_create(f2,NULL,NO_PRIORITY); // 5 
    tid_t six = thread_create(f1,NULL,NO_PRIORITY); // 6
    thread_join(four);
    thread_join(five);
    thread_join(six);
    thread_libterminate();

    for (int i = 0; i < 3; i++){
        if (arr[i] != expected[i]){
            printf("Unexpected order\n");
            return EXIT_FAILURE;
        }
    }
    // thread_yield();
    printf("SUCCESS\n");
    return EXIT_SUCCESS;

    }