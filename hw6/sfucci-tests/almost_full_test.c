#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

/*

Almost full test.

This defrags a disk image that 
contains a single used inode thats data uses 100 blocks.
There are 101 blocks total, namely, block 13 is the only free block.

This test forks a process to defragment this disk image, and 
then reads in the result. This tests that
upon defragmentation, the only free block is at block 100 
(assuming that the indices are 0-indexed).
This is done by checking that block 100 is the start of the free list
and then by checking that block 100's first 4 bytes are -1, 
assuring the list is properly linked.

How to compile: gcc -o almost_full_test almost_full_test.c -Wall -g
How to run: ./almost_full_test

*/
int main(){

  pid_t pid;

  if((pid = fork())==0){

    char *arg_arr[3];
    arg_arr[0] = "./defrag";
    arg_arr[1] = "almost-full-img";
    arg_arr[2] = '\0';

    execvp("./defrag", arg_arr);
    exit(EXIT_SUCCESS);
    
  }else{
    int status;
    waitpid(pid,&status, 0);

    FILE * new_img = fopen("almost-full-img-defrag","r");
    void * data = malloc(1024);

    fread(data,1,1024,new_img);

    struct superblock * sblock = (struct superblock *) (data+512);
    assert(sblock->free_block == 100);

    fseek(new_img, 1024 +(512 *sblock->data_offset)+(100*512), SEEK_SET);
    int * val = malloc(4);
    fread(val, 1,4,new_img);

    assert(*val == -1);
    free(data);
    free(val);
    fclose(new_img);
    printf("Success\n");
    
  }

}
