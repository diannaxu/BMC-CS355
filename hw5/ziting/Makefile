CC=gcc
CFLAGS=-g -Wall

all: mem_init_misuse simple_8_byte simple_8_byte_coalesce simple_aligned simple_odd mem_init_1_page mem_init_1_page_roundup free_null_pointer memory_writable

mem_init_misuse: mem_init_misuse.c libmem.so
	$(CC) $(CFLAGS) mem_init_misuse.c -o mem_init_misuse -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

simple_8_byte: simple_8_byte.c libmem.so
	$(CC) $(CFLAGS) simple_8_byte.c -o simple_8_byte -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

simple_8_byte_coalesce: simple_8_byte_coalesce.c libmem.so
	$(CC) $(CFLAGS) simple_8_byte_coalesce.c -o simple_8_byte_coalesce -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

simple_aligned: simple_aligned.c libmem.so
	$(CC) $(CFLAGS) simple_aligned.c -o simple_aligned -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

simple_odd: simple_odd.c libmem.so
	$(CC) $(CFLAGS) simple_odd.c -o simple_odd -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

mem_init_1_page: mem_init_1_page.c libmem.so
	$(CC) $(CFLAGS) mem_init_1_page.c -o mem_init_1_page -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

mem_init_1_page_roundup: mem_init_1_page_roundup.c libmem.so
	$(CC) $(CFLAGS) mem_init_1_page_roundup.c -o mem_init_1_page_roundup -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

free_null_pointer: free_null_pointer.c libmem.so
	$(CC) $(CFLAGS) free_null_pointer.c -o free_null_pointer -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

memory_writable: memory_writable.c libmem.so
	$(CC) $(CFLAGS) memory_writable.c -o memory_writable -L. -lmem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

clean:
	rm mem_init_misuse simple_8_byte simple_8_byte_coalesce simple_aligned simple_odd mem_init_1_page mem_init_1_page_roundup free_null_pointer memory_writable
