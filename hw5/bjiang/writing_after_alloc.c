//Author: Ben Jiang
//Tests writing the allocated memory

#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 7
#define FAIL -1

int main(){

    if(Mem_Init(4096) == FAIL){
        return EXIT_FAILURE;
    }
    int *my_int = (int *)Mem_Alloc(sizeof(int));
    *my_int = 3782;
    if(*my_int != 3782){return EXIT_FAILURE;}

    char *my_string[5] = (char *)Mem_Alloc(sizeof(char*) * 5);
    my_string[0] = "hi!";
    my_string[1] = "I love OS";
    my_string[2] = "I love OS homeworks";
    my_string[3] = "Do I though?";
    my_string[4] = "I don't know.";

    if(strcmp(my_string[2], "I love OS homeworks") != 0){return EXIT_FAILURE;}

    return EXIT_SUCCESS;
}