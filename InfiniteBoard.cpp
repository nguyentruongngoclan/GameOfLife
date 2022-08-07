#include "include/GameOfLifeState.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <stdlib.h>

constexpr int kDefaultTick = 10;

bool readInputFromFile(const std::string& fileName, std::set<Coordinate>& inputs) {	
	std::string line;
	std::ifstream inputFile(fileName);
	if (inputFile.is_open()) {
		long long x, y;
		while (std::getline(inputFile, line)) {
			std::stringstream ss(line);
			ss >> x >> y;
			inputs.insert({x,y});
		}
	} else {		
		return false;
	}
	return true;
}

void runGameOfLife(long long numOfTicks, std::set<Coordinate>& inputs) {
	GameOfLifeState gameOfLifeState(inputs);
	// Print the initial state
	gameOfLifeState.printState(std::cout);
	for (int tick = 0; tick < numOfTicks; ++tick) {
		gameOfLifeState.tick();
		// Print to standard output
		gameOfLifeState.printState(std::cout);
	}	
}

void readFromStdInput(std::set<Coordinate>& inputs) {
	long long x, y;
	std::string line = {};
	std::string prompt = 		
		"Provides live cells x and y coordinates, separated by space, for example : 1 2. \nPress enter and repeat to keep adding live cells \nTo end, give a end of file input (i.e: Ctrl-Z in Windows, Ctrl-D in *nix)\n";
	std::cout << prompt << std::endl;
	while (std::getline(std::cin, line)) {
		std::stringstream ss(line);
		ss >> x >> y; 
		inputs.insert({x,y});			
	}
}

int main(int argc, const char* argv[]) {
	std::set<Coordinate> inputs = {};
	long long ticks = kDefaultTick;
	std::string fileName = {};
	// Parse flags if any
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i],"-f") == 0) {								
			if (i+1 >= argc) {
				std::cout << "Missing file input, terminated" << std::endl;
				return 0;
			}
			fileName = argv[i+1];
			if (!readInputFromFile(fileName, inputs)) {
				std::cout << "Cannot open file, please check the directory again" << std::endl;
				return 0;
			}
		}
		if (strcmp(argv[i],"-t") == 0) {								
			if (i+1 >= argc) {
				std::cout << "Missing tick input, terminated" << std::endl;
				return 0;
			}
			ticks = strtoll(argv[i+1], NULL, 10);
		}
	}			
	// If there's no input files, we'll takes inputs from std input
	if (fileName.empty()) {		
		readFromStdInput(inputs);	
	}
	runGameOfLife(ticks, inputs);
	
	return 0;
}