 #include "MisereTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

MisereBoard::MisereBoard() : Board<char>(3, 3) {
    board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    n_moves = 0;
}

bool MisereBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool MisereBoard::is_win(Player<char>* player) {
    return false;
}

bool MisereBoard::is_lose(Player<char>* player) {
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

bool MisereBoard::is_draw(Player<char>* player) {
    return n_moves == 9 && !is_lose(player);
}

bool MisereBoard::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}

void MisereBoard::display_board() {
    cout << "\n-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

MisereUI::MisereUI() : UI<char>("Welcome to Misere Tic-Tac-Toe (Anti Tic-Tac-Toe)!", 3) {}

Move<char>* MisereUI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "'s turn (symbol: " << player->get_symbol() << ")\n";
        
        while (true) {
            cout << "Enter row (0-2): ";
            cin >> x;
            cout << "Enter column (0-2): ";
            cin >> y;

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "Invalid coordinates! Must be between 0-2. Try again.\n";
                continue;
            }

            auto boardMatrix = player->get_board_ptr()->get_board_matrix();
            if (boardMatrix[x][y] == ' ') {
                break;
            } else {
                cout << "Cell is already occupied! Try again.\n";
            }
        }
    } else {
        auto boardMatrix = player->get_board_ptr()->get_board_matrix();
        
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (boardMatrix[x][y] != ' ');

        cout << player->get_name() << " played (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* MisereUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}