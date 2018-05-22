all: main

main: main.o operation.o optype.o
	g++ main.o operation.o optype.o -o main -std=c++11

operation.o: Operation.cpp Operation.h
	g++ -c Operation.cpp -o operation.o -std=c++11

optype.o: Optype.cpp Optype.h
	g++ -c Optype.cpp -o optype.o -std=c++11

main.o: main.cpp Operation.h Optype.h
	g++ -c main.cpp -o main.o -std=c++11

clean:
	rm *.o main