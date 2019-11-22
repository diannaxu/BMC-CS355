all: almost_full_test data_test full_test link_test

almost_full_test: almost_full_test.c structs.h
	gcc -o almost_full_test almost_full_test.c -Wall -g
data_test: data_test.c structs.h
	gcc -o data_test data_test.c -Wall -g
full_test: full_test.c structs.h
	gcc -o full_test full_test.c -Wall -g
link_test: link_test.c structs.h
	gcc -o link_test link_test.c -Wall -g
