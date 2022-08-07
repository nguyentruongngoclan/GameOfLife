#include "GameOfLifeState.h"

#include <limits.h>
#include <iostream>

namespace {
	constexpr std::pair<int,int> directions[8] = {
		{-1, -1}, // top-left
		{-1, 0}, // top
		{-1, 1}, // top-right
		{0, -1}, // left	
		{0, 1}, // right
		{1, -1}, // bottom-left
		{1, 0}, // bottom
		{1, 1}, // bottom-right
	};
	// Check if there're potential overflow before applying direction to the current row / col
	bool isWithinBoundary(long long row, long long col, std::pair<int, int> direction) {
		if (row == LLONG_MIN && direction.first == -1) return false;
		if (col == LLONG_MIN && direction.second == -1) return false;
		if (row == LLONG_MAX && direction.first == 1) return false;
		if (col == LLONG_MAX && direction.second == 1) return false;
		return true;
	}
}

// Retrieves all non-live cells adjacent to the current live cells
std::set<Coordinate> GameOfLifeState::getCandidateNonLiveCells() {
	// We only care about cells that have have at least 1 neighbor live cells
	// and doesn't really need to scan a full board, which is very slow with infinite board
	
	std::set<Coordinate> candidateCells = {};
	for (const auto &liveCell : liveCells_) {
		for (const auto& direction : directions) {
			// For each direction wrt current liveCell, add all its neighbor non-live, if not out of bound
			// TODO: Check for overflows before computing checkRow & checkColumn
			long long checkRow = liveCell.first + direction.first; 
			long long checkCol = liveCell.second + direction.second;
			if (
				liveCells_.find({checkRow, checkCol}) == liveCells_.end() // is not a live cell
			) {
				candidateCells.insert({checkRow, checkCol});
			}
		}
	}
	return candidateCells;
}

int GameOfLifeState::countLiveStatus(long long row, long long col){
	int count = 0;	
	for (const auto& direction : directions) {
		// For each direction wrt current (row,col), check their status (live/dead) and increment count if found a live		
		if (!isWithinBoundary(row,col,direction)) continue;
		long long checkRow = row + direction.first; 
		long long checkCol = col + direction.second;

		// Increment count if (checkRow,checkCol) belongs to liveCells
		if (liveCells_.find({checkRow,checkCol}) != liveCells_.end()) {
			++count;
		}		
	}
	return count;
}

void GameOfLifeState::tick() {
	// 1. Allocate newLiveCells representing the new tick's live cells. liveCells_ is considered past tick's live cell
	// 2. Grab a new list of candidate non-live cells to check against as they are candidate to be modified
	// 3. For each candidate cells:
	//		3.a Do the neighbor counts against the past-tick liveCells
	//		3.b Determine its status based on the current count
	//		3.c Add them to newLiveCells if status is live
	// 4. For each liveCells_:
	//		4.a Do the neighbor counts against the past-tick liveCells
	//		4.b Determine its status based on the current count
	//		4.c Add them to newLiveCells if status is live
	// 5. Assign newLiveCells to liveCells
	
	// 1.
	std::set<Coordinate> newLiveCells = {};
	// 2
	const auto nonLiveCandidateCells = getCandidateNonLiveCells();
	// 3.
	for (const auto& nonLiveCandidateCell : nonLiveCandidateCells) {
		//	3.a
		const auto liveCount = countLiveStatus(nonLiveCandidateCell.first, nonLiveCandidateCell.second);
		//	3.b
		if (liveCount == 3) {
			// 3.c
			newLiveCells.insert(nonLiveCandidateCell);
		}
		else {

		}
	}
	// 4.
	for (const auto& pastTickLiveCell : liveCells_) {
		// 4.a
		const auto liveCount = countLiveStatus(pastTickLiveCell.first, pastTickLiveCell.second);
		// 4.b
		if (liveCount == 2 || liveCount == 3) {
			// 4.c
			newLiveCells.insert(pastTickLiveCell);
		}
		// Otherwise the cell is considered dead and not added into the next tick
	}
	// 5.
	liveCells_ = newLiveCells;
}

void GameOfLifeState::printState(std::ostream& ostream) {
	ostream << "#Life 1.06" << std::endl;
	for (const auto& liveCell : liveCells_) {
		ostream << liveCell.first << " " << liveCell.second << std::endl;		
	}	
}