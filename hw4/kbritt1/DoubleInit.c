//Trying to initalize userthread lib twice.
#include "userthread.h"


int main(){
    int err;
    err = thread_libinit(SJF);
    if (err != 0) {
        printf("FAILED\n");
        return -1;
    }
    err = thread_libinit(FCFS);
    if (err != -1 ) {
        printf("FAILED\n");
        return -1;
    }
    pritnf("SUCCESS\n");
    return 0;
    }   