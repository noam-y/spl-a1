make: all

all: clean compile link run

clean:
	rm -f ./bin/*
 
compile : src/Auxiliary.cpp src/main.cpp src/Simulation.cpp src/SelectionPolicy.cpp src/Settlement.cpp src/Facility.cpp src/FacilityType.cpp
	g++ -c -Wall -g -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -c -Wall -g -Iinclude -o bin/main.o src/main.cpp
	g++ -c -Wall -g -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -c -Wall -g -Iinclude -o bin/Settlement.o src/Settlement.cpp
	g++ -c -Wall -g -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -c -Wall -g -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -c -Wall -g -Iinclude -o bin/FacilityType.o src/FacilityType.cpp

 
link : bin/main.o bin/Auxiliary.o bin/Simulation.o bin/Settlement.o bin/SelectionPolicy.o bin/Facility.o bin/FacilityType.o 
	g++ -o bin/program bin/main.o bin/Auxiliary.o bin/Simulation.o bin/Settlement.o bin/SelectionPolicy.o bin/Facility.o bin/FacilityType.o 

run :
	bin/program config_file.txt
