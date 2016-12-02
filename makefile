MAIN=src/main.c
SRCS := $(filter-out $(MAIN),$(wildcard src/*.c))
CFLAGS=-g -I src/ -Wall
.PHONY: clean test all

all:
	gcc -o somlg $(CFLAGS) ${SRCS} ${MAIN}

run: all
	./gam-test

%test:
	gcc $(CFLAGS) tests/$@.c $(SRCS) -lcmocka -o bin/$@
	valgrind bin/$@

clean:
	rm -rf somlg bin/*
