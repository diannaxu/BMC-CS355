/*
author: Yue Chen
The program is to test basic functioins: create with arg and join
*/
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

struct ABC{
    int a;
    int b;
    int c;
};

void a(void* abc){
    struct ABC *temp = (struct ABC*)abc;
    printf("%d %d %d \n",temp->a,temp->b,temp->c);
}

int main(){
    if(thread_libinit(FIFO)==0){
        printf("FIFO Scheduling\n");
    }else{
        printf("Failed to Schedule\n");
        exit(EXIT_FAILURE);
    }
    struct ABC test ={1,2,3};
    for(int i=0;i<5;i++){
        if(thread_create(a,(void *)&test,0)==-1){
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0;i<5;i++){
        if(thread_join(i)==-1){
            printf("failed to join thread %d\n",i);
        }
    }
    if(thread_libterminate()!=0){
        printf("Failed to Libterminate \n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}