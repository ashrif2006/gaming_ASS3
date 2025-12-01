include "MemoryTicTacToe.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>


using namespace std;

MemoryBoard::MemoryBoard() : Board<char>(3, 3), currentPlayer('X') {
    board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    revealed = {
       {false, false, false},
       {false, false, false},
       {false, false, false}
    };
}

bool MemoryBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = symbol;
    n_moves++;

	revealed[x][y] = true; // Mark the cell as revealed
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

bool MemoryBoard::is_win(Player<char>* player) {
	char symbol = player->get_symbol();
    
    for(int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return true;
	}

    if(board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
		return true;
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
		return true;
    return false;
}
bool MemoryBoard::is_lose(Player<char>* player) {
	char player2_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';    
    for(int i = 0; i < 3; i++) {
        if (board[i][0] == player2_symbol && board[i][1] == player2_symbol && board[i][2] == player2_symbol)
            return true;
        if (board[0][i] == player2_symbol && board[1][i] == player2_symbol && board[2][i] == player2_symbol)
            return true;
    }
    if(board[0][0] == player2_symbol && board[1][1] == player2_symbol && board[2][2] == player2_symbol)
		return true;
    if (board[0][2] == player2_symbol && board[1][1] == player2_symbol && board[2][0] == player2_symbol)
        return true;
    return false;
}
bool MemoryBoard::is_draw(Player<char>* player) {
    return (n_moves >= 9) && !is_win(player) && !is_lose(player); // Draw if all cells are filled
}
bool MemoryBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

void MemoryBoard::reveal_all() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            revealed[i][j] = true;
        }
    }
}

void MemoryBoard::hide_all() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            revealed[i][j] = false;
        }
    }
}
bool MemoryBoard::is_revealed(int x, int y) const {
    return revealed[x][y];
}
void MemoryBoard::reveal_position(int x, int y) {
    revealed[x][y] = true;
}

//reveal current board state
void MemoryBoard::display_memory_board() const {
    cout << "\nCurrent Memory Board:\n";
    cout << "  0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            if (revealed[i][j]) {
                cout << board[i][j];
            }
            else {
                cout << "?";
            }
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "  ---------\n";
    }
    cout << endl;
}

MemoryTicTacToeUI::MemoryTicTacToeUI() : UI<char>("Welcome to Memory Tic-Tac-Toe!", 13) {}
Move<char>* MemoryTicTacToeUI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();
    auto board_ptr = dynamic_cast<MemoryBoard*>(player->get_board_ptr());
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        while (true) {
            cout << "\n" << player->get_name() << "'s turn (symbol: " << symbol << ")\n";
            
            cout << "Enter position to reveal (row column): ";
            cin >> x >> y;
            if (x < 0 || x >= 3 || y < 0 || y >= 3) {
                cout << "Invalid coordinates! Please enter numbers between 0 and 2.\n";
                continue;
            }
            if (board_matrix[x][y] != ' ') {
                cout << "That position is already revealed! Please choose a hidden cell.\n";
                continue;
            }
            break;
        }
        return new Move<char>(x, y, symbol);
    }
    else {
        // Computer player - random move
        vector<pair<int, int>> hidden_cells;
        // Find all hidden cells
        auto board_matrix = board_ptr->get_board_matrix();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board_matrix[i][j] == ' ') {
                    hidden_cells.push_back({ i, j });
                }
            }
        }
        if (!hidden_cells.empty()) {
            auto move_pos = hidden_cells[rand() % hidden_cells.size()];
            cout << player->get_name() << " (Computer) reveals position (" << move_pos.first << "," << move_pos.second << ")\n";
            return new Move<char>(move_pos.first, move_pos.second, symbol);
        }
        return new Move<char>(0, 0, symbol);
    }
}
Player<char>* MemoryTicTacToeUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
};
