make: init init_simple bad_init_args coalesce capacity wf_1 wf_2 aligned_alloc space space_2 free_misuse

init_simple: init_simple.c
	gcc -o init_simple init_simple.c -L.. -lmem
init: init.c
	gcc -o init init.c -L.. -lmem
bad_init_args: bad_init_args.c
	gcc -o bad_init_args bad_init_args.c -L.. -lmem
coalesce: coalesce.c
	gcc -o coalesce coalesce.c -L.. -lmem
capacity: capacity.c
	gcc -o capacity capacity.c -L.. -lmem
wf_1: wf_1.c
	gcc -o wf_1 wf_1.c -L.. -lmem
wf_2: wf_2.c
	gcc -o wf_2 wf_2.c -L.. -lmem
aligned_alloc: aligned_alloc.c
	gcc -o aligned_alloc aligned_alloc.c -L.. -lmem
space: space.c
	gcc -o space space.c -L.. -lmem
space_2: space_2.c
	gcc -o space_2 space_2.c -L.. -lmem

free_misuse: free_misuse.c
	gcc -o free_misuse free_misuse.c -L.. -lmem
