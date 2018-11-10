CC := gcc
CFLAGS := -g3 -masm=intel 

9cc: 9cc.c 9cc.h

test: 9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp* a.out core

debug: 9cc
	./9cc '1+2*3'
