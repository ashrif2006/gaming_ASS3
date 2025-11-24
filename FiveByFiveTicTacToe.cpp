#include "FiveByFiveTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

FiveByFiveBoard::FiveByFiveBoard() : Board<char>(5, 5), currentPlayer('X') {
    board = {
        {' ', ' ', ' ',' ',' '},
        {' ', ' ', ' ',' ',' '},
        {' ', ' ', ' ',' ',' '},
        {' ', ' ', ' ',' ',' '},
        {' ', ' ', ' ',' ',' '}
    };
}

// Virtual function from Board<char>
bool FiveByFiveBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

bool FiveByFiveBoard::is_win(Player<char>* player) {
    if (n_moves < 24) return false;

    char player_symbol = player->get_symbol();
    char player2_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_row(player_symbol);
    int player2_score = count_three_in_row(player2_symbol);

    return player_score > player2_score;
}

bool FiveByFiveBoard::is_lose(Player<char>* player) {
    if (n_moves < 24) return false;

    char player_symbol = player->get_symbol();
    char player2_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_row(player_symbol);
    int player2_score = count_three_in_row(player2_symbol);

    return player_score < player2_score;
}

bool FiveByFiveBoard::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char player_symbol = player->get_symbol();
    char player2_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_row(player_symbol);
    int player2_score = count_three_in_row(player2_symbol);

    return player_score == player2_score;
}

bool FiveByFiveBoard::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}


int FiveByFiveBoard::count_three_in_row(char symbol) {
    int count = 0;

    // Check horizontal sequences
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check vertical sequences
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal sequences (top-left to bottom-right)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal sequences (top-right to bottom-left)
    for (int i = 0; i < 3; i++) {
        for (int j = 2; j < 5; j++) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

FiveByFiveUI::FiveByFiveUI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe!", 6) {}

Move<char>* FiveByFiveUI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();
    auto board_ptr = dynamic_cast<FiveByFiveBoard*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;

        while (true) {
            cout << "\n" << player->get_name() << "'s turn (symbol: " << symbol << ")\n";

            // Display available moves
            cout << "Available moves: ";
            bool first_move = true;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (board_ptr->get_cell(i, j) == ' ') {
                        if (!first_move) cout << ", ";
                        cout << "(" << i << "," << j << ")";
                        first_move = false;
                    }
                }
            }
            cout << endl;

            cout << "Enter position (row column): ";
            cin >> x >> y;

            if (x < 0 || x >= 5 || y < 0 || y >= 5) {
                cout << "Invalid coordinates! Please enter numbers between 0 and 4.\n";
                continue;
            }

            if (board_ptr->get_cell(x, y) != ' ') {
                cout << "That position is already taken! Please choose an empty cell.\n";
                continue;
            }

            break;
        }

        return new Move<char>(x, y, symbol);
    }
    else {
        // Computer player - random move
        vector<pair<int, int>> empty_cells;

        // Find all empty cells
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board_ptr->get_cell(i, j) == ' ') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (!empty_cells.empty()) {
            auto move = empty_cells[rand() % empty_cells.size()];
            cout << player->get_name() << " (Computer) chooses position ("
                << move.first << "," << move.second << ")\n";
            return new Move<char>(move.first, move.second, symbol);
        }

        return new Move<char>(0, 0, symbol);
    }
}

Player<char>* FiveByFiveUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

