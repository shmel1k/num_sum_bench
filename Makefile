all: build
	./main

build:
	g++ main.cpp -Lbenchmark/build/src -lbenchmark -lpthread -o main
