all: program1 program2 program3

program1: program1.cpp
	g++ program1.cpp -o program1
program2: program2.cpp
	g++ program2.cpp -o program2
program3: program3.cpp
	g++ program3.cpp -o program3

clean:
	rm program1
	rm program2
	rm program3
	rm *.o
