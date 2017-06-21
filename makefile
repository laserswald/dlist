CFLAGS=--std=c11 -O1

all: test check

test: test.c dlist.h
	gcc -g -o test test.c

check:
	exec ./test

.PHONY: check

