make: all

all: clean compile link run

clean:
	rm -f ./bin/*

compile : src/Auxiliary.cpp src/main.cpp
	g++ -c -Wall -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -c -Wall -o bin/main.o src/main.cpp

link : bin/main.o bin/Auxiliary.o
	g++ -o bin/program bin/main.o bin/Auxiliary.o

run : bin/program
	bin/program config_file.txt
