#include <iostream>
#include <set>
#include <vector>
#include <utility>

using namespace std;
constexpr int kBoardWidth = 4;
constexpr int kBoardHeight = 4;
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

int countLiveStatus(vector<vector<int>>&board, int row, int col){
	int count = 0;
	
	for (const auto& direction : directions) {
		// For each direction wrt current (row,col), check their status (live/dead) and increment count if found a live
		int checkRow = row + direction.first; 
		int checkCol = col + direction.second;
		if (
			checkRow >= 0
			&& checkRow < kBoardHeight
			&& checkCol >= 0
			&& checkCol < kBoardWidth) {
				// A board at (checkRow,checkCol) is considered live if
				// it was previously live (1), or was newly dead (2) due to past iterations
				if (board[checkRow][checkCol] == 1 || board[checkRow][checkCol] == 2) {
					++count;
				}
		}
	}
	//cout << "num lives at (" << row << "," << col << ") = " << count << endl;
	
	return count;
}

void drawBoard(vector<vector<int>>&board) {
	cout << "Draw board ===============" << endl;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[0].size(); ++j) {
			//cout << (board[i][j] == 0 ? '.' : 'x');
			cout << board[i][j];
		}
		cout << endl;
	}
}
int main() {	
	vector<vector<int>> board(kBoardHeight, vector<int>(kBoardWidth, 0));
	vector<pair<int,int>> inputs = {
		{0,1},
		{1,2},
		{2,0},
		{2,1},
		{2,2}
	};
	for (const auto& input : inputs) {
		board[input.first][input.second] = 1;
	}
	drawBoard(board);
	vector<vector<pair<int,int>>> liveCellsPerTick = {};
	// Do a 10-iterations
	for (int tick = 0; tick < 10; ++tick) {		
		liveCellsPerTick.push_back({});
		// We do 2 passes here
		// first will update the table in-place with new values
		// 0 = dead
		// 1 = live
		// 2 = newly dead
		// 3 = newly alive
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[0].size(); ++j) {
				int numLives = countLiveStatus(board, i, j);
				if (board[i][j] == 0) { // current cell is dead
					if (numLives == 3) {
						board[i][j] = 3; // Newly alive						
					}
				} else { // current cell is alive
					if (
						numLives < 2 // under-populated
						|| numLives > 3 // over-populated					
					) { // current cell should be dead
						board[i][j] = 2; // Newly dead
					}
				}				
			}			
		}
		//drawBoard(board);
		// then we'll rewrite the newly update values with the original value
		cout << "Tick " << tick << ": ";
		for (int i = 0; i < board.size(); ++i) {			
			for (int j = 0; j < board[0].size(); ++j) {
				// shift by 2 so newly dead -> dead & newly live -> live
				board[i][j] = board[i][j] >= 2 ? board[i][j] - 2 : board[i][j];
				if (board[i][j] == 1) {
					liveCellsPerTick[tick].push_back({i,j});
					cout << "(" << i << "," << j << ")";
				}
			}			
		}
		cout << endl;
		// for (int t = 0; t < liveCellsPerTick.size(); ++t) {
		// 	cout << "Tick " << t << ": ";
		// 	for (int i = 0; i < liveCellsPerTick[t].size(); ++i) {
		// 		cout << "(" << liveCellsPerTick[t][i].first << "," << liveCellsPerTick[t][i].second << ")";
		// 	}
		// 	cout << endl;
		// }
		//drawBoard(board);		
	}	
	return 0;
}