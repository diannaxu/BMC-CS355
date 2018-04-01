CC=gcc
CFLAGS=-g -Wall

all: mem_init_misuse

mem_init_misuse: mem_init_misuse.c libmem.so
	$(CC) $(CFLAGS) mem_init_misuse.c -o mem_init_misuse -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
