CFLAGS=-O3 --std=gnu17

build: src/main.c
	clang $(CFLAGS) src/main.c -o bin/hypertrav

