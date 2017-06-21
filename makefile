CFLAGS=--std=c11 -O1

all: test check

test: test.c dlist.h
	gcc -g -o test test.c

debug: dlist.h test.c
	cpp -P test.c | indent -linux >debug.c

check:
	exec ./test

.PHONY: check

