#!/bin/sh
make >> log.txt
echo "If nothing prints out after this line, then you pass the tests. Otherwise check log.txt."
echo "./mem_init_misuse----------------------" >> log.txt
./mem_init_misuse >> log.txt
echo "./simple_8_byte----------------------" >> log.txt
./simple_8_byte >> log.txt
echo "./simple_8_byte_coalesce----------------------" >> log.txt
./simple_8_byte_coalesce >> log.txt
echo "./simple_aligned----------------------" >> log.txt
./simple_aligned simple_odd >> log.txt
echo "./mem_init_1_page----------------------" >> log.txt
./mem_init_1_page >> log.txt
echo "./mem_init_1_page_roundup----------------------" >> log.txt
./mem_init_1_page_roundup >> log.txt
echo "./free_null_pointer----------------------" >> log.txt
./free_null_pointer >> log.txt
echo "./memory_writable----------------------" >> log.txt
./memory_writable >> log.txt
echo "./allocate_all_memory----------------------" >> log.txt
./allocate_all_memory >> log.txt
echo "./allocate_too_much----------------------" >> log.txt
./allocate_too_much worst_fit >> log.txt
grep assert < log.txt