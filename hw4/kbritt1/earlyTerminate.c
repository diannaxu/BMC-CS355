//Trying to terminate threadlib when it hasn't been initialized.
#include "userthread.h"

int main(){
    int err;
    err = thread_libterminate();
    if (err != -1){
        pritnf("FAILURE\n");
        return EXIT_FAILURE;
    }
    pritnf("SUCCESS\n");

    return EXIT_SUCCESS;

}