#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "mem.h"

#define FAILURE -1
#define TRUE 1
#define FALSE 0

#define NUMBER_UNIT_TESTS 13

// test funcs
void eight_byte_allignment(void);
void large_alloc_and_free_no_coalesce(void);
void eight_byte_allocation(void);
void alligned_allocations(void);
void odd_sized_allocations(void);
void misuses(void);
void worst_fit(void);
void coalesce_free_space(void);
void page_size(void);
void round_up_to_page_size(void);
void no_space_left_to_allocate(void);
void check_memory_can_be_written_to(void);
void large_alloc_and_free_coalesce(void);

void FisherYates(int *array, int n);

void (*test_funcs[NUMBER_UNIT_TESTS])(void) = {
	eight_byte_allignment,
	eight_byte_allocation,
	alligned_allocations,
	odd_sized_allocations,
	misuses,
	worst_fit,
	coalesce_free_space,
	page_size,
	round_up_to_page_size,
	no_space_left_to_allocate,
	check_memory_can_be_written_to,
	large_alloc_and_free_no_coalesce,
	large_alloc_and_free_coalesce
};

char *unit_test_names[NUMBER_UNIT_TESTS] = {
	"eight_byte_allignment",
	"eight_byte_allocation",
	"alligned_allocations",
	"odd_sized_allocations",
	"misuses",
	"worst_fit",
	"coalesce_free_space",
	"page_size",
	"round_up_to_page_size",
	"no_space_left_to_allocate",
	"large_alloc_and_free_no_coalesce",
	"large_alloc_and_free_coalesce",
	"check_memory_can_be_written_to"

};

char *error_chars[5] = {
	"E_NO_SPACE",
	"E_CORRUPT_FREESPACE",
	"E_PADDING_OVERWRITTEN",
	"E_BAD_ARGS",
	"E_BAD_POINTER"
};

char *result_char[2] = {
  "SUCCESS",
  "FAILURE"
};

typedef struct t1 {
	int first;
} t1;

typedef struct t2 {
	int first;
	int second;
} t2;

typedef struct t3 {
	int first;
	int second;
	int third;
} t3;

/**
 * Start eight byte alignment test
 */
void eight_byte_allignment(void)
{
	int allocs = 10;

	printf(" * Testing eight byte allignment...\n");
	printf(" * Should return success if all allocations 8 byte alligned memory...\n");

	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}
	
	void **ptrs = malloc(sizeof(void *) * allocs);

	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc(sizeof(int));

		if (ptrs[i] == NULL) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}

		if ( ((long) ptrs[i]) % 8 != 0 ) {
			fprintf(stderr, "Not 8 byte alligned\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}


/**
 * Start eight_byte_allocation test
 */
void eight_byte_allocation(void)
{
	int allocs = 1;
	int bytes = 8;

	printf(" * Testing eight byte allocation...\n");
	printf(" * Should see size of header plus eight bytes in size of free'd block on dump...\n");

	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}
	
	void **ptrs = malloc(sizeof(void *) * allocs);
	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc(bytes);

		if (ptrs[i] == NULL) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	Mem_Dump();

	free(ptrs);
	exit(EXIT_SUCCESS);
}

/**
 * Start Alligned allocations test
 */
void alligned_allocations(void)
{
	int allocs = 5;

	printf (" * Testing alligned allocations...\n");
	printf(" * On free of aligned allocaitons, should see 6 free blocks, five of which are of same size\n");
	printf(" * and all are aligned in memory\n");

	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	void **ptrs = malloc(sizeof(void *) * allocs);

	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc(sizeof(t3));

		if (ptrs[i] == NULL) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	Mem_Dump();

	free(ptrs);
	exit(EXIT_SUCCESS);

}

/**
 * Start odd sized allocations test
 */
void odd_sized_allocations(void)
{
	int allocs = 5;

	printf(" * Testing odd sized allocations...\n");
	printf(" * On free of aligned allocaitons, should see 6 free blocks of varying sizes\n");
	printf(" * and all are aligned in memory\n");

	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	void **ptrs = malloc(sizeof(void *) * allocs);

	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc((i*i*i*i) + 1);
		if (ptrs[i] == NULL || (long) ptrs[i] % 8 != 0) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	Mem_Dump();

	free(ptrs);
	exit(EXIT_SUCCESS);
}

/**
 * Start bad args for init test
 */
void misuses(void)
{
	printf(" * Testing misuses...\n");
	printf(" * Should return success on completion...\n");

	if (Mem_Init(0) != FAILURE)
		exit(EXIT_FAILURE);

	if (Mem_Init(1) == FAILURE)
		exit(EXIT_FAILURE);

	if (Mem_Init(1) != FAILURE)
		exit(EXIT_FAILURE);

	t3 *test_struct;

	// initialize size should be rounded up to pagesize
	if ((test_struct = Mem_Alloc(sizeof(t3))) == NULL)
		exit(EXIT_FAILURE);

	// no action occurs on null free, false 
	if (Mem_Free(NULL, FALSE) == FAILURE)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}

/**
 * Start worst fit test
 */
void worst_fit(void)
{
	int allocs = 5;

	printf(" * Testing worst fit...\n");
	printf(" * Should see largest block removed from free list throughout dumps...\n");


	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	void **ptrs = malloc(sizeof(void *) * allocs);

	int sizes[allocs];

	sizes[0] = 3200;
	sizes[1] = 64;
	sizes[2] = 24;
	sizes[3] = 576;
	sizes[4] = 72;

	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc((sizes[i]));
		if (ptrs[i] == NULL || (long) ptrs[i] % 8 != 0) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 1; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	Mem_Dump();

	if (Mem_Alloc(sizes[3]) == NULL)
		exit(EXIT_FAILURE);

	Mem_Dump();

	if (Mem_Alloc(sizes[4]) == NULL)
		exit(EXIT_FAILURE);

	Mem_Dump();

	if (Mem_Alloc(sizes[1]) == NULL)
		exit(EXIT_FAILURE);

	Mem_Dump();

	free(ptrs);
	exit(EXIT_SUCCESS);
}

/**
 * Start coalesce free space test
 */
void coalesce_free_space(void)
{
	int allocs = 5;

	printf(" * Testing coalescing free space...\n");
	printf(" * Should see one continuos block of memory in dump...\n");


	if (Mem_Init(allocs * 50) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	void **ptrs = malloc(sizeof(void *) * allocs);

	for (int i = 0; i < allocs; ++i)
	{
		ptrs[i] = Mem_Alloc((sizeof(t3)) + 1);
		if (ptrs[i] == NULL || (long) ptrs[i] % 8 != 0) {
			fprintf(stderr, "Failure allocating\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 1; i < allocs; ++i)
	{
		if (Mem_Free(ptrs[i], FALSE) == FAILURE) {
			fprintf(stderr, "Failure freeing\n");
			exit(EXIT_FAILURE);
		}
	}

	if (Mem_Free(ptrs[0], TRUE) == FAILURE)
		exit(EXIT_FAILURE);

	Mem_Dump();

	free(ptrs);
	exit(EXIT_SUCCESS);
}

void page_size(void)
{
	printf(" * Testing to make sure allocaiton rounds to page size...\n");
	printf(" * Block Size in dump should be same size as page size...\n");

	long int page_size = getpagesize();

	printf(" * This machines page size: %ld ", page_size);

	if (Mem_Init(page_size) == FAILURE)
		exit(EXIT_FAILURE);

	Mem_Dump();

	exit(EXIT_SUCCESS);
}

void round_up_to_page_size(void)
{
	printf(" * Testing to make sure allocaiton rounds to page size...\n");
	printf(" * Block Size in dump should be same size as page size...\n");

	long int page_size = getpagesize();

	printf(" * This machines page size: %ld ", page_size);

	if (Mem_Init(1) == FAILURE)
		exit(EXIT_FAILURE);

	Mem_Dump();

	exit(EXIT_SUCCESS);
}

void no_space_left_to_allocate(void)
{
	printf(" * Testing to make sure allocation fails as desired...\n");
	printf(" * Should print out allocation failure on E_NO_SPACE...\n");

	if (Mem_Init(getpagesize()) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	// alloc should fail because there's not enough room for a header
	if (Mem_Alloc(getpagesize()) == NULL) {
		printf("Alloc failed on error code %s \n", error_chars[m_error - 1]);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}

void check_memory_can_be_written_to(void)
{
	printf(" * Testing to make memory can be written to...\n");
	printf(" * Should return sucess on good completion...\n");

	if (Mem_Init(getpagesize()) == FAILURE) {
		fprintf(stderr, "Failure initializing\n");
		exit(EXIT_FAILURE);
	}

	t1 *test1; t2 *test2; t3 *test3;

	if ((test1 = Mem_Alloc(sizeof(t1))) == NULL)
		exit(EXIT_FAILURE);

	test1->first = 100;

	if ((test2 = Mem_Alloc(sizeof(t2))) == NULL)
		exit(EXIT_FAILURE);

	test2->first = 200;
	test2->second = 300;

	if ((test3 = Mem_Alloc(sizeof(t3))) == NULL)
		exit(EXIT_FAILURE);

	test3->first = 400;
	test3->second = 500;
	test3->third = 600;

	if (test1->first != 100)
		exit(EXIT_FAILURE);

	if (test2->first != 200 || test2->second != 300)
		exit(EXIT_FAILURE);

	if (test3->first != 400 || test3->second != 500 || test3->third != 600)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}

/**
 * Start large_alloc_and_free_no_coalesce test
 */

// https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
void FisherYates(int *array, int n) { //implementation of Fisher
     int i, j, tmp; // create local variables to hold values for shuffle
     srand(time(0));
     for (i = n - 1; i > 0; i--) { // for loop to shuffle
         j = rand() % (i + 1); //randomise j for shuffle with Fisher Yates
         tmp = array[j];
         array[j] = array[i];
         array[i] = tmp;
     }
}

void large_alloc_and_free_no_coalesce(void)
{
	int allocs = 2000000;
	int free_freq = 100;
	int seed = 15;

	int *free_order;
	free_order = calloc(allocs, sizeof(*free_order));

	for (int i = 0; i < allocs; i++) 
		free_order[i] = i;
	
	// shuffle list to get non repeating sequence of frees 
	FisherYates(free_order, allocs);

	void **ptrs = malloc(sizeof(void*) * allocs);

	if (Mem_Init(allocs * 100) == FAILURE) {
		exit(EXIT_FAILURE);
	}

	printf(" * Testing large array allocation and free without coalescing\n");
	printf(" * Using %d allocs and freeing every %d allocs \n", allocs, free_freq);
	printf(" * Frees are performed after allocation and are memory chunks in random order\n");

	clock_t first_test = clock();

	srand(seed);

	for (int i = 0; i < allocs; ++i)
	{
		int alloc_struct = rand() % (3);
		if (alloc_struct == 0)
			ptrs[i] = Mem_Alloc(sizeof(t1));
		else if (alloc_struct == 1)
			ptrs[i] = Mem_Alloc(sizeof(t2));
		else
			ptrs[i] = Mem_Alloc(sizeof(t3));
	}


	for (int i = 0; i < allocs/free_freq; ++i)
	{
		if (Mem_Free(ptrs[free_order[i]], FALSE) == FAILURE)
			exit(EXIT_FAILURE);
	}

	clock_t end_first_test = clock();
	double time_spent = (double)(end_first_test - first_test) / CLOCKS_PER_SEC;

	printf(" * The user malloc implementation took %f seconds...\n", time_spent);

	first_test = clock();

	srand(seed);

	for (int i = 0; i < allocs; ++i)
	{
		int alloc_struct = rand() % (3);
		if (alloc_struct == 0)
			ptrs[i] = malloc(sizeof(t1));
		else if (alloc_struct == 1)
			ptrs[i] = malloc(sizeof(t2));
		else
			ptrs[i] = malloc(sizeof(t3));
	}

	for (int i = 0; i < allocs/free_freq; ++i)
	{
		free(ptrs[free_order[i]]);
	}

	end_first_test = clock();
	time_spent = (double)(end_first_test - first_test) / CLOCKS_PER_SEC;
	printf(" * The same test with malloc took %f seconds...\n", time_spent);

	free(ptrs);
	free(free_order);
	exit(EXIT_SUCCESS);
}

void large_alloc_and_free_coalesce(void)
{
	int allocs = 2000000;
	int free_freq = 10000;
	int seed = 15;

	int *free_order;
	free_order = calloc(allocs, sizeof(*free_order));

	for (int i = 0; i < allocs; i++) 
		free_order[i] = i;
	
	// shuffle list to get non repeating sequence of frees 
	FisherYates(free_order, allocs);

	void **ptrs = malloc(sizeof(void*) * allocs);

	if (Mem_Init(allocs * 100) == FAILURE) {
		exit(EXIT_FAILURE);
	}

	printf(" * Testing large array allocation and free with coalescing\n");
	printf(" * Using %d allocs and freeing every %d allocs \n", allocs, free_freq);
	printf(" * Frees are performed after allocation and are memory chunks in random order\n");

	clock_t first_test = clock();

	srand(seed);

	for (int i = 0; i < allocs; ++i)
	{
		int alloc_struct = rand() % (3);
		if (alloc_struct == 0)
			ptrs[i] = Mem_Alloc(sizeof(t1));
		else if (alloc_struct == 1)
			ptrs[i] = Mem_Alloc(sizeof(t2));
		else
			ptrs[i] = Mem_Alloc(sizeof(t3));
	}


	for (int i = 0; i < allocs/free_freq; ++i)
	{
		if (Mem_Free(ptrs[free_order[i]], TRUE) == FAILURE)
			exit(EXIT_FAILURE);
	}

	clock_t end_first_test = clock();
	double time_spent = (double)(end_first_test - first_test) / CLOCKS_PER_SEC;

	printf(" * The user malloc implementation took %f seconds...\n", time_spent);

	first_test = clock();

	srand(seed);

	for (int i = 0; i < allocs; ++i)
	{
		int alloc_struct = rand() % (3);
		if (alloc_struct == 0)
			ptrs[i] = malloc(sizeof(t1));
		else if (alloc_struct == 1)
			ptrs[i] = malloc(sizeof(t2));
		else
			ptrs[i] = malloc(sizeof(t3));
	}

	for (int i = 0; i < allocs/free_freq; ++i)
	{
		free(ptrs[free_order[i]]);
	}

	end_first_test = clock();
	time_spent = (double)(end_first_test - first_test) / CLOCKS_PER_SEC;
	printf(" * The same test with malloc took %f seconds...\n", time_spent);

	free(ptrs);
	free(free_order);
	exit(EXIT_SUCCESS);
}

/**
 * Main test loop
 */
int main(int argc, char *argv[]) 
{

  int test_one_function = FALSE;
  int location_of_func = -1;
  int number_of_successes = 0;

  printf("--------------------------\n");

  /**
   * handle  -n flags
   */
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-n") == 0) {
      if (i + 1 < argc) {
        char *name_of_desire_func = argv[i+1];
        for (int j = 0; j < NUMBER_UNIT_TESTS; j++)
        {
          if (strcmp(name_of_desire_func, unit_test_names[j]) == 0) {
            printf("Running test only for %s \n", unit_test_names[j]);
            test_one_function = TRUE;
            location_of_func = j;
          }
        }
      }
    }
  }

  printf("Beginning Test Suite...\n");
  printf("--------------------------\n");

  int current_test_count = 0;
  int num_tests_considered = 0;
  int pid;
  while (current_test_count < NUMBER_UNIT_TESTS) {
    num_tests_considered++;
    pid = fork();
    if (pid == 0) {
      if (test_one_function)
        (*test_funcs[location_of_func]) ();
      else
        (*test_funcs[current_test_count]) ();
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        int wstatus;
        wait(&wstatus);    
        if (test_one_function)
          current_test_count = location_of_func;
        printf("Test ~%s~ exited with status... %s\n", unit_test_names[current_test_count],\
         result_char[WEXITSTATUS(wstatus)]);
        if (WEXITSTATUS(wstatus) == EXIT_SUCCESS)
          number_of_successes++;
        printf("--------------------------\n");
      
      current_test_count++;
      if (test_one_function) { break; }
    }
  }

  printf(" * Unit Test Complete.\n * %d out of %d returned successfully.\n", number_of_successes, num_tests_considered);

  return EXIT_SUCCESS;
}
