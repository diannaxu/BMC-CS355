#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define N 10


/*
Tests that you can store and execute function pointers
Should print 'Hello!' N times

Used:
https://stackoverflow.com/questions/5488608/how-define-an-array-of-function-pointers-in-c

to figure out how to declare an array of function pointers
*/

typedef void (*fp) (void);

void sample(){
  printf("Hello!\n");
}
int main(){
  if(Mem_Init(N*sizeof(fp)) == -1){
    exit(EXIT_FAILURE);
  }

  fp funcs[N];

  for(int i = 0; i < N; i++){
    void* ptr = Mem_Alloc(sizeof(fp));
    fp func = (fp) ptr;
    func = sample;
    funcs[i] = func;
    
  }

  /*
  Executing the functions
   */
  for(int i = 0; i < N; i++){
    funcs[i]();
  }
  
  exit(EXIT_SUCCESS);
}
