 #include "ObstaclesTicTacToe.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

ObstaclesTicTacToeBoard::ObstaclesTicTacToeBoard() : Board(6, 6), roundCount(0) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

bool ObstaclesTicTacToeBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;

    // Add obstacles after every complete round
    if (n_moves % 2 == 0) {
        roundCount++;
        int obstacles = 0;
        while (obstacles < 2) {
            int rx = rand() % rows;
            int ry = rand() % columns;
            if (board[rx][ry] == ' ') {
                board[rx][ry] = '#';
                obstacles++;
            }
        }
    }

    return true;
}

bool ObstaclesTicTacToeBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    
    // Check rows
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == symbol && board[i][j+1] == symbol && 
                board[i][j+2] == symbol && board[i][j+3] == symbol)
                return true;
        }
    }
    
    // Check columns
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == symbol && board[i+1][j] == symbol && 
                board[i+2][j] == symbol && board[i+3][j] == symbol)
                return true;
        }
    }
    
    // Check diagonals
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && 
                board[i+2][j+2] == symbol && board[i+3][j+3] == symbol)
                return true;
        }
    }
    
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && 
                board[i+2][j-2] == symbol && board[i+3][j-3] == symbol)
                return true;
        }
    }
    
    return false;
}

bool ObstaclesTicTacToeBoard::is_lose(Player<char>* player) {
    return false; // Not used in this game
}

bool ObstaclesTicTacToeBoard::is_draw(Player<char>* player) {
    // Check if board is full
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

bool ObstaclesTicTacToeBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

 // UI Implementation
ObstaclesTicTacToeUI::ObstaclesTicTacToeUI() : UI("Obstacles Tic-Tac-Toe", 3) {}

Move<char>* ObstaclesTicTacToeUI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "'s turn (symbol: " << player->get_symbol() << ")\n";
        cout << "Enter row (0-5): ";
        cin >> x;
        cout << "Enter column (0-5): ";
        cin >> y;
    } else {
        // Computer makes random move
        Board<char>* board = player->get_board_ptr();
        vector<vector<char>> matrix = board->get_board_matrix();
        
        // Find all empty cells
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < board->get_rows(); i++) {
            for (int j = 0; j < board->get_columns(); j++) {
                if (matrix[i][j] == ' ') {
                    emptyCells.push_back({i, j});
                }
            }
        }
        
        if (emptyCells.empty()) {
            // No moves available (shouldn't happen in normal game)
            x = 0; y = 0;
        } else {
            // Choose random empty cell
            int randomIndex = rand() % emptyCells.size();
            x = emptyCells[randomIndex].first;
            y = emptyCells[randomIndex].second;
        }
        
        cout << player->get_name() << " (Computer) plays at (" << x << ", " << y << ")\n";
    }
    
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* ObstaclesTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
