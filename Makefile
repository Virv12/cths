run: main
	./main

main: main.cpp cths.h
	g++ -std=c++20 -Ofast -Wall -Wextra -Wpedantic -o $@ $<

.PHONY: run
