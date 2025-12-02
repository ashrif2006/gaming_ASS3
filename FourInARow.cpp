#include "FourInARow.h"
#include <iostream>
using namespace std;

FourInARowBoard::FourInARowBoard() : Board<char>(6, 7) {
	
	for(int i=0; i<6; i++)
		for(int j=0; j<7; j++)
			board[i][j] = ' ';
	n_moves = 0;
}


bool FourInARowBoard::update_board(Move<char>* move) {
	int col = move->get_y();
	if(col < 0 || col >= 7)
		return false;
	for (int row = 5; row >= 0; row--) {
		if (board[row][col] == ' ') {
			board[row][col] = move->get_symbol();
			n_moves++;
			return true;
		}
	}


	return false; 
}

bool FourInARowBoard::is_win(Player<char>* player) {
	char sym = player->get_symbol();
	//الافقي 
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 4; c++) {
			if (board[r][c] == sym && board[r][c + 1] == sym &&
				board[r][c + 2] == sym && board[r][c + 3] == sym) {
				return true;
			}
		}
	}
	// العمودي
	for (int c = 0; c < 7; c++) {
		for (int r = 0; r < 3; r++) {
			if (board[r][c] == sym && board[r + 1][c] == sym &&
				board[r + 2][c] == sym && board[r + 3][c] == sym) {
				return true;
			}
		}
	}
	// المقصى (bottom-left to top-right)
	for (int r = 3; r < 6; r++) {
		for (int c = 0; c < 4; c++) {
			if (board[r][c] == sym && board[r - 1][c + 1] == sym &&
				board[r - 2][c + 2] == sym && board[r - 3][c + 3] == sym) {
				return true;
			}
		}
	}
	// المقص (top-left to bottom-right)
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 4; c++) {
			if (board[r][c] == sym && board[r + 1][c + 1] == sym &&
				board[r + 2][c + 2] == sym && board[r + 3][c + 3] == sym) {
				return true;
			}
		}
	}
	return false;
}

bool FourInARowBoard::is_lose(Player<char>* player) {
	return false; 
}

bool FourInARowBoard::is_draw(Player<char>* player) {
	return n_moves == 42 && !is_win(player);
}

bool FourInARowBoard::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

/////////////////////////////
//FourInARow UI
/////////////////////////////

FourInARowUI::FourInARowUI() : UI<char>("Welcome to Four In A Row!", 7) {}
Move<char>* FourInARowUI::get_move(Player<char>* player) {
	int col;
	if (player->get_type() == PlayerType::HUMAN) {
		cout << player->get_name() << "'s turn. Enter column (0-6): ";
		cin >> col;
	} else {
		col = rand() % 7;
		cout << player->get_name() << " (AI) chooses column " << col << endl;
	}
	return new Move<char>(-1, col, player->get_symbol());
}

Player<char>* FourInARowUI::create_player(std::string& name, char symbol, PlayerType type) {
	return new Player<char>(name, symbol, type);
}

