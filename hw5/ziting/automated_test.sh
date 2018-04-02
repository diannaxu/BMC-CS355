#!/bin/sh
rm log.txt
make >> log.txt
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
echo "If nothing prints out after this line, then you pass the tests. Otherwise check log.txt."
./mem_init_misuse >> log.txt
./simple_8_byte >> log.txt
./simple_8_byte_coalesce >> log.txt
./simple_aligned simple_odd >> log.txt
./mem_init_1_page >> log.txt
./mem_init_1_page_roundup >> log.txt
./free_null_pointer >> log.txt
./memory_writable >> log.txt
./allocate_all_memory >> log.txt
./allocate_too_much worst_fit >> log.txt
grep assert < log.txt