#include <ostream>
#include <set>
#include <utility>
#include <vector>

using Coordinate = std::pair<long long, long long>;

class GameOfLifeState {
	static constexpr std::pair<int, int> directions[8] = {
		{-1, -1}, // top-left
		{-1, 0}, // top
		{-1, 1}, // top-right
		{0, -1}, // left	
		{0, 1}, // right
		{1, -1}, // bottom-left
		{1, 0}, // bottom
		{1, 1}, // bottom-right
	};
	public:
		GameOfLifeState(std::set<Coordinate> liveCells) : liveCells_(liveCells) {};

		// Advance the game of life to the next state
		void tick();
		
		// Prints the state of the game of life in 1.06 format
		void printState(std::ostream& ostream);
	private:
		// Retrieves all non-live cells adjacent to the current live cells
		std::set<Coordinate> getCandidateNonLiveCells();

		// Counts how many live cells adjacent to the current cell at (row,col)
		int countLiveStatus(long long row, long long col);
		std::set<Coordinate> liveCells_;

};