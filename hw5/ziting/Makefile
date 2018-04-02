CC=gcc
CFLAGS=-g -Wall

all: mem_init_misuse simple_8_byte simple_8_byte_coalesce simple_aligned simple_odd mem_init_1_page mem_init_1_page_roundup free_null_pointer memory_writable allocate_all_memory allocate_too_much worst_fit

mem_init_misuse: mem_init_misuse.c libmem.so
	$(CC) $(CFLAGS) mem_init_misuse.c -o mem_init_misuse -L. -lmem

simple_8_byte: simple_8_byte.c libmem.so
	$(CC) $(CFLAGS) simple_8_byte.c -o simple_8_byte -L. -lmem

simple_8_byte_coalesce: simple_8_byte_coalesce.c libmem.so
	$(CC) $(CFLAGS) simple_8_byte_coalesce.c -o simple_8_byte_coalesce -L. -lmem

simple_aligned: simple_aligned.c libmem.so
	$(CC) $(CFLAGS) simple_aligned.c -o simple_aligned -L. -lmem

simple_odd: simple_odd.c libmem.so
	$(CC) $(CFLAGS) simple_odd.c -o simple_odd -L. -lmem

mem_init_1_page: mem_init_1_page.c libmem.so
	$(CC) $(CFLAGS) mem_init_1_page.c -o mem_init_1_page -L. -lmem

mem_init_1_page_roundup: mem_init_1_page_roundup.c libmem.so
	$(CC) $(CFLAGS) mem_init_1_page_roundup.c -o mem_init_1_page_roundup -L. -lmem

free_null_pointer: free_null_pointer.c libmem.so
	$(CC) $(CFLAGS) free_null_pointer.c -o free_null_pointer -L. -lmem

memory_writable: memory_writable.c libmem.so
	$(CC) $(CFLAGS) memory_writable.c -o memory_writable -L. -lmem

allocate_all_memory: allocate_all_memory.c libmem.so
	$(CC) $(CFLAGS) allocate_all_memory.c -o allocate_all_memory -L. -lmem

allocate_too_much: allocate_too_much.c libmem.so
	$(CC) $(CFLAGS) allocate_too_much.c -o allocate_too_much -L. -lmem

worst_fit: worst_fit.c libmem.so
	$(CC) $(CFLAGS) worst_fit.c -o worst_fit -L. -lmem

clean:
	rm mem_init_misuse simple_8_byte simple_8_byte_coalesce simple_aligned simple_odd mem_init_1_page mem_init_1_page_roundup free_null_pointer memory_writable allocate_all_memory allocate_too_much worst_fit
