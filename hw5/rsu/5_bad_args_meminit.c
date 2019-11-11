/*
Test for bad arguments to meminit: <=0 arguments, calling meminit after an successful init
use assert to make sure <=0 arguments fail, regular meminit succeed, calling meminit after successful init fail
Expected behavior: exit normally
*/

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1
#define EIGHT_BYTES 8
#define NUM_ALLOCS 100
#define ALLOC_SIZE 8

int main() {
  int requested = Mem_Init(-111);
  assert(requested == FAIL);
  Mem_Dump();

  requested = Mem_Init(0);
  assert(requested == FAIL);
  Mem_Dump();

  requested = Mem_Init(128);
  assert(requested == SUCCESS);
  Mem_Dump();

  requested = Mem_Init(800);
  assert(requested == FAIL);
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
