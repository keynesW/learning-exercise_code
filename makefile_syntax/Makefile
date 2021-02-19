tst:test.o test-Copy.o 
	cc -o tst test.o test-Copy.o -g
test.o:test.c test-Copy.h
	cc -c test.c
test-Copy:test-Copy.c test-Copy.h
	cc -c test-Copy.c
clean:
	rm tst test.o test-Copy.o 
