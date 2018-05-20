all: main

main: main.o operation.o
	g++ main.o operation.o -o main -std=c++11

operation.o: operation.cpp operation.h
	g++ -c operation.cpp -o operation.o -std=c++11

main.o: main.cpp operation.h
	g++ -c main.cpp -o main.o -std=c++11

clean:
	rm *.o main