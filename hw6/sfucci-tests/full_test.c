#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

/*
  Tests that a defragmented image that has no free blocks
  has no elements on its free list.

  Reads in full-img, a disk image with all 100 blocks being used by a single inode 
(99 to store the data and an indirect block). 

This tests that the defragmented disk image's free_block pointer points to -1, showing that
there are no free blocks.

How to compile: gcc -o full_test full_test.c -Wall -g
How to run: ./full_test 

****Make sure you have full-img in the same directory
 and that your defragmentor fallows the naming convention!**** 
*/
int main(){

  pid_t pid;

  if((pid = fork())==0){

    char *arg_arr[3];
    arg_arr[0] = "./defrag";
    arg_arr[1] = "full-img";
    arg_arr[2] = '\0';

    execvp("./defrag", arg_arr);
    exit(EXIT_SUCCESS);
    
  }else{
    int status;
    waitpid(pid,&status, 0);

    FILE * new_img = fopen("full-img-defrag","r");
    void * data = malloc(1024);

    fread(data,1,1024,new_img);

    struct superblock * sblock = (struct superblock *) (data+512);
    assert(sblock->free_block == -1);
    free(data);
    
  }

}
