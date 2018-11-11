CC := gcc
#CFLAGS=-Wall -std=c11 -g3 -masm=intel 
CFLAGS=-std=c11 -g3 -masm=intel 
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

9cc: $(OBJS)
	cc -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): 9cc.h

test: 9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp* a.out core

debug: 9cc
	#./9cc '2*3+4*5'
	#./9cc '1+2*3'
	./9cc '2*3+1'

format: 
	clang-format -i *.c *.h
