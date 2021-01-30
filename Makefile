CFLAGS=-O3 --std=gnu17
CPPFLAGS=-O3 --std=c++20

c-posix: src/c-posix.c
	clang $(CFLAGS) src/c-posix.c -o auto-c-posix

cpp-stl: src/stl.cpp
	clang++ $(CPPFLAGS) src/stl.cpp -o auto-cpp-stl

