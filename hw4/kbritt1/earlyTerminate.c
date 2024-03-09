//Trying to terminate threadlib when it hasn't been initialized.
#include "userthread.h"

int main(){
    int err;
    err = thread_libterminate();
    if (err != -1){
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }
    printf("SUCCESS\n");

    return EXIT_SUCCESS;

}