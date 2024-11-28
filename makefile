make: all

all: clean compile link run

clean:
	rm -f ./bin/*

compile : src/Auxiliary.cpp src/main.cpp src/Simulation.cpp
	g++ -c -Wall -g -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -c -Wall -g -Iinclude -o bin/main.o src/main.cpp
	g++ -c -Wall -g -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -c -Wall -g -Iinclude -o bin/Settlement.o src/Settlement.cpp

link : bin/main.o bin/Auxiliary.o bin/Simulation.o bin/Settlement.o
	g++ -o bin/program bin/main.o bin/Auxiliary.o bin/Simulation.o bin/Settlement.o

run : bin/program
	bin/program config_file.txt
