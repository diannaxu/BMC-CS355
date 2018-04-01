#!/bin/sh
make
./mem_init_misuse
./simple_8_byte
./simple_8_byte_coalesce
./simple_aligned simple_odd
./mem_init_1_page
./mem_init_1_page_roundup
./free_null_pointer
./memory_writable
./allocate_all_memory 
./allocate_too_much worst_fit