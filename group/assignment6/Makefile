all: main
	./main 
	
main: main.o Assignment6.h Assignment6_test.h Assignment6.o Assignment6_test.o
	g++ main.o Assignment6.o Assignment6_test.o -o main

main.o: main.cpp 
	g++ -c main.cpp -o main.o

Assignment6.o: Assignment6.cpp Assignment6.h
	g++ -c Assignment6.cpp -o Assignment6.o

Assignment6_test.o: Assignment6_test.cpp Assignment6_test.h
	g++ -c Assignment6_test.cpp -o Assignment6_test.o

clean: 
	rm *.o main


