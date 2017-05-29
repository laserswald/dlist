CFLAGS=--std=c11

all: test check

test: test.c dlist.h
	gcc -g -o test test.c

check:
	exec ./test

.PHONY: check

