CFLAGS=-O3 --std=gnu17

build: src/main.c
	gcc $(CFLAGS) src/main.c -o bin/hypertrav

