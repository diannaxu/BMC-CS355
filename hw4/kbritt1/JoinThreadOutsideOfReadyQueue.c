//thread three joins thread two which is waiting for one to complete

#include "userthread.h"
int count = 0;
int arr[3] = {0};
int expected[3] = {1,2,3};


struct info{
    int num;
    tid_t to_join;
};


void f1(void * info){
    struct info * unpack = info;
    tid_t to_join = unpack->to_join;
    int num = unpack->num;
    thread_join(to_join);
    arr[count++] = num;
    free(info);
}
void f2(void * info){
    thread_yield();
    struct info * unpack = info;
    arr[count++] = unpack->num;
    free(info); 
}

struct info * makeInfo(int num, tid_t to_join){
    struct info * new_info = malloc(sizeof(struct info));
    new_info->num = num;
    new_info->to_join = to_join;
    return new_info;
}

int main(){
    thread_libinit(SJF);
    tid_t one = thread_create(f2,makeInfo(1,0),NO_PRIORITY); // 1 0 not used
    tid_t two = thread_create(f1,makeInfo(2,one),NO_PRIORITY); // 2
    tid_t three=  thread_create(f1,makeInfo(3,two),NO_PRIORITY);// 3 joining thread two which has already joined 1.
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