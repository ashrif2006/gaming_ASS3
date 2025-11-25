#include "InfinityTicTacToe.h"
#include <iostream>
#include<limits>

using namespace std;
InfinityTicTacToe::InfinityTicTacToe() : Board<char>(3,3) {
	board = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '} 
	};
	n_moves = 0;
	
}
//bool InfinityTicTacToe::update_board(Move<char>* move) {
//	int row = move->get_row();
//	int col = move->get_col();
//	char symbol = move->get_symbol();
//	// Expand the board if the move is outside current boundaries
//	while (row < 0) {
//		board.insert(board.begin(), vector<char>(columns, ' '));
//		rows++;
//		row++;
//	}
//	while (row >= rows) {
//		board.push_back(vector<char>(columns, ' '));
//		rows++;
//	}
//	while (col < 0) {
//		for (auto& r : board) {
//			r.insert(r.begin(), ' ');
//		}
//		columns++;
//		col++;
//	}
//	while (col >= columns) {
//		for (auto& r : board) {
//			r.push_back(' ');
//		}
//		columns++;
//	}
//	// Check if the cell is already occupied
//	if (board[row][col] != ' ') {
//		return false; // Invalid move
//	}
//	// Place the symbol on the board
//	board[row][col] = symbol;
//	n_moves++;
//	moves_history.push({row, col});
//	return true;
//}

bool InfinityTicTacToe::update_board(Move<char>* move) {
	int r = move->get_x();
	int c = move->get_y();
	char symbol = move->get_symbol();

	if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != ' ') {
		return false; // Invalid move
	}
	board[r][c] = symbol;
	
	n_moves++;
	moves_history.push({ r, c });

	if (n_moves % 3 == 0) {
		int x = moves_history.front().first;
		int y = moves_history.front().second;
		board[x][y] = ' ';
		moves_history.pop();

	}
	return true;
	
}

bool InfinityTicTacToe::is_win(Player<char>* player) {
	char symbol = player->get_symbol();

	// التحقق من الصفوف
	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
			return true;
	}

	// التحقق من الأعمدة
	for (int j = 0; j < 3; ++j) {
		if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
			return true;
	}

	// التحقق من القطرين
	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
		return true;
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
		return true;

	return false;
}
bool InfinityTicTacToe::is_lose(Player<char>* player) {
	return false;
}
bool InfinityTicTacToe::is_draw(Player<char>* player) {
	return false;
}
bool InfinityTicTacToe::game_is_over(Player<char>* player) {
	return is_win(player);
}

// UI Implementation
InfinityTicTacToeUI::InfinityTicTacToeUI() : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 3) {}
Move<char>* InfinityTicTacToeUI::get_move(Player<char>* player) {
	char symbol = player->get_symbol();
	int row, col;
	if (player->get_type() == PlayerType::HUMAN) {
		while (true) {
			cout << player->get_name() << "'s turn (symbol: " << symbol << ")\n";
			cout << "Enter your move (row and column): ";
			cin >> row >> col;
			// Validate input
			if (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter valid row and column numbers.\n";
				continue;
			}
			break;
		}
	} else {
		// Simple AI: choose the first available cell
		auto boardMatrix = player->get_board_ptr()->get_board_matrix();
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (boardMatrix[i][j] == ' ') {
					row = i;
					col = j;
					cout << player->get_name() << " (AI) chooses: " << row << " " << col << "\n";
					return new Move<char>(row, col, symbol);
				}
			}
		}
	}
	return new Move<char>(row, col, symbol);
}
Player<char>* InfinityTicTacToeUI::create_player(std::string& name, char symbol, PlayerType type) {
	return new Player<char>(name, symbol, type);
}