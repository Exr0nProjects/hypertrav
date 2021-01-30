CPPFLAGS=-O2 --std=c++20

cpp-stl: src/stl.cpp
	clang++ $(CPPFLAGS) src/stl.cpp -o auto-cpp-stl

