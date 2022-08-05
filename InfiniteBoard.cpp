#include "include/GameOfLifeState.h"

#include <utility>
#include <vector>

int main() {	
	// vector<vector<int>> board(kBoardHeight, vector<int>(kBoardWidth, 0));
	std::set<std::pair<int,int>> inputs = {
		{0,1},
		{1,2},
		{2,0},
		{2,1},
		{2,2}
	};
	GameOfLifeState gameOfLifeState(inputs);	
	// Do a 10-iterations
	for (int tick = 1; tick <= 10; ++tick) {
		gameOfLifeState.tick();
		gameOfLifeState.printState();		
	}	
	return 0;
}