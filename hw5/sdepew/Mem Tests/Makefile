all: cleanFirst mem Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 Test11 Test12 Test13 Test14 Test15 cleanLast

Test1:
	gcc -g -ggdb -o Test1 Test1.c -L. -lmem

Test2:
	gcc -g -ggdb -o Test2 Test2.c -L. -lmem

Test3:
	gcc -g -ggdb -o Test3 Test3.c -L. -lmem

Test4:
	gcc -g -ggdb -o Test4 Test4.c -L. -lmem

Test5:
	gcc -g -ggdb -o Test5 Test5.c -L. -lmem

Test6:
	gcc -g -ggdb -o Test6 Test6.c -L. -lmem

Test7:
	gcc -g -ggdb -o Test7 Test7.c -L. -lmem

Test8:
	gcc -g -ggdb -o Test8 Test8.c -L. -lmem

Test9:
	gcc -g -ggdb -o Test9 Test9.c -L. -lmem

Test10:
	gcc -g -ggdb -o Test10 Test10.c -L. -lmem

Test11:
	gcc -g -ggdb -o Test11 Test11.c -L. -lmem

Test12:
	gcc -g -ggdb -o Test12 Test12.c -L. -lmem

Test13:
	gcc -g -ggdb -o Test13 Test13.c -L. -lmem

Test14:
	gcc -g -ggdb -o Test14 Test14.c -L. -lmem

Test15:
	gcc -g -ggdb -o Test15 Test15.c -L. -lmem

mem: mem.o helper.o list.o
	gcc -g -ggdb -o libmem.so mem.o helper.o list.o -shared

mem.o: ../../mem.c ../../mem.h
	gcc -g -ggdb -Wall -fpic -c ../../mem.c

helper.o: ../../helper.c ../../helper.h
	gcc -g -ggdb -Wall -fpic -c ../../helper.c

list.o: ../../list.c ../../list.h
	gcc -g -ggdb -Wall -fpic -c ../../list.c

cleanFirst:
	rm -rf *.o *.gch *.dSYM Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 Test11 Test12 Test13 Test14 Test15

cleanLast:
	rm -rf *.o *.gch *.dSYM