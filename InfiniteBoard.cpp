#include <iostream>
#include <limits.h>
#include <set>

#include <vector>
#include <utility>

using namespace std;

constexpr pair<int,int> directions[8] = {
	{-1, -1}, // top-left
	{-1, 0}, // top
	{-1, 1}, // top-right
	{0, -1}, // left	
	{0, 1}, // right
	{1, -1}, // bottom-left
	{1, 0}, // bottom
	{1, 1}, // bottom-right
};

int countLiveStatus(set<pair<int,int>>& liveCells, int row, int col){
	int count = 0;	
	for (const auto& direction : directions) {
		// For each direction wrt current (row,col), check their status (live/dead) and increment count if found a live		
		// TODO: Check for overflows before computing checkRow & checkColumn
		int checkRow = row + direction.first; 
		int checkCol = col + direction.second;
		if (
			checkRow > INT_MIN
			&& checkRow < INT_MAX
			&& checkCol >= INT_MIN
			&& checkCol < INT_MAX) {
				// Increment count if (checkRow,checkCol) belongs to liveCells
				if (liveCells.find({checkRow,checkCol}) != liveCells.end()) {
					++count;
				}				
		}
	}
	//cout << "num lives at (" << row << "," << col << ") = " << count << endl;	
	return count;
}

set<pair<int,int>> getCandidateNonLiveCells(set<pair<int,int>> &liveCells) {
	// We only care about cells that have have at least 1 neighbor live cells
	// and doesn't really need to scan a full board, which is very slow with infinite board
	
	set<pair<int,int>> candidateCells = {};
	for (const auto &liveCell : liveCells) {
		for (const auto& direction : directions) {
			// For each direction wrt current liveCell, add all its neighbor non-live, if not out of bound
			// TODO: Check for overflows before computing checkRow & checkColumn
			int checkRow = liveCell.first + direction.first; 
			int checkCol = liveCell.second + direction.second;
			if (			
				checkRow > INT_MIN
				&& checkRow < INT_MAX
				&& checkCol >= INT_MIN
				&& checkCol < INT_MAX 
				&& liveCells.find({checkRow, checkCol}) == liveCells.end() // is not a live cell
			) {
				candidateCells.insert({checkRow, checkCol});
			}
		}
	}
	return candidateCells;
}
int main() {	
	// vector<vector<int>> board(kBoardHeight, vector<int>(kBoardWidth, 0));
	set<pair<int,int>> inputs = {
		{0,1},
		{1,2},
		{2,0},
		{2,1},
		{2,2}
	};	
	vector<set<pair<int,int>>> liveCellsPerTick = {};
	liveCellsPerTick.push_back(inputs);
	
	// For each iteration:
	// 1. Grab a new list of candidate non-live cells to check against as they are candidate to be modified
	// 2. For each candidate cells:
	//		2.a Do the neighbor counts against the past-tick liveCells
	//		2.b Determine its status based on the current count
	//		2.c Add them to the current's tick live cell if status is live
	// 3. For each previously live cells:
	//		3.a Do the neighbor counts against the past-tick liveCells
	//		3.b Determine its status based on the current count
	//		3.c Add them to the current's tick live cell if status is live	
	// Do a 10-iterations
	for (int tick = 1; tick <= 10; ++tick) {
		set<pair<int,int>> pastTickLiveCells = liveCellsPerTick[tick - 1];
		liveCellsPerTick.push_back({});
		cout << "Tick " << tick << ": ";
		// 1. Grab a new list of candidate non-live cells to check against as they are candidate to be modified
		const auto nonLiveCandidateCells = getCandidateNonLiveCells(pastTickLiveCells);
		// 2. For each candidate cells:
		for (const auto& nonLiveCandidateCell : nonLiveCandidateCells) {
			//		2.a Do the neighbor counts against the past-tick liveCells
			int liveCount = countLiveStatus(pastTickLiveCells, nonLiveCandidateCell.first, nonLiveCandidateCell.second);
			//		2.b Determine its status based on the current count
			if (liveCount == 3) {
				//		2.c Add them to the current's tick live cell if status is live
				liveCellsPerTick[tick].insert(nonLiveCandidateCell);
				cout << "(" << nonLiveCandidateCell.first << "," << nonLiveCandidateCell.second << ")";
			}
		}
		// 3. For each previously live cells:
		for (const auto& pastTickLiveCell : pastTickLiveCells) {
			//		3.a Do the neighbor counts against the past-tick liveCells
			int liveCount = countLiveStatus(pastTickLiveCells, pastTickLiveCell.first, pastTickLiveCell.second);
			//		3.b Determine its status based on the current count
			if (liveCount == 2 || liveCount == 3) {
				//		3.c Add them to the current's tick live cell if status is live	
				liveCellsPerTick[tick].insert(pastTickLiveCell);
				cout << "(" << pastTickLiveCell.first << "," << pastTickLiveCell.second << ")";
			}
			// Otherwise the cell is considered dead and not added into the next tick
		}
		cout << endl;
	}	
	return 0;
}