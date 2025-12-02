#include "NumericalTicTacToe.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <algorithm>

#include <set>

using namespace std;



NumericalBoard::NumericalBoard() : Board<int>(3, 3) {
    board = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    n_moves = 0;
}

bool NumericalBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int val = move->get_symbol();

   
    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != 0)
        return false; 

    board[x][y] = val;
    n_moves++;
    return true;
}


bool NumericalBoard::is_win(Player<int>* player) {
    int target = 15; 

  // check rows
    for (int i = 0; i < 3; ++i)
        if (board[i][0] + board[i][1] + board[i][2] == target) return true;

  //check columns
    for (int j = 0; j < 3; ++j)
        if (board[0][j] + board[1][j] + board[2][j] == target) return true;

  //check diagonals
    if (board[0][0] + board[1][1] + board[2][2] == target) return true;
    if (board[0][2] + board[1][1] + board[2][0] == target) return true;

    return false;
}


bool NumericalBoard::is_lose(Player<int>* player) {
    return false; 
}

bool NumericalBoard::is_draw(Player<int>* player) {
    return n_moves == 9&& !is_win(player);
}

bool NumericalBoard::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

/////////////////////////////
// NumericalUI
/////////////////////////////

NumericalUI::NumericalUI() : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 3) {}

Move<int>* NumericalUI::get_move(Player<int>* player) {
    int x, y, val;

    // مجموعات أرقام اللاعبين
    vector<int> odd_numbers  = {1, 3, 5, 7, 9};
    vector<int> even_numbers = {2, 4, 6, 8};

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "'s turn\n";

        while (true) {
            cout << "Enter row (0-2): ";
            cin >> x;
            cout << "Enter column (0-2): ";
            cin >> y;

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "Invalid coordinates! Must be between 0-2. Try again.\n";
                continue;
            }
            cout << "Enter number to place: ";
            cin >> val;

            bool isPlayer1 = (player->get_symbol() == 'X');  // Check if this is Player X

            if (isPlayer1) {
                // Player 1 = odd numbers
                if (val == 1 || val == 3 || val == 5 || val == 7 || val == 9) {
                    break;
                }
                else {
                    cout << "Player 1 must use odd numbers (1,3,5,7,9)! Try again.\n";
                }
            }
            else {
                // Player 2 = even numbers  
                if (val == 2 || val == 4 || val == 6 || val == 8) {
                    break;
                }
                else {
                    cout << "Player 2 must use even numbers (2,4,6,8)! Try again.\n";
                }
            }

            // تحقق من أن الخانة فارغة
            bool empty_cell = (player->get_board_ptr()->get_board_matrix()[x][y] == 0);

            if (empty_cell) break;

            cout << "Invalid move! Number or cell is not allowed. Try again.\n";
        }
    } else {
        // AI: اختيار رقم صحيح ومكان فارغ
        auto boardMatrix = player->get_board_ptr()->get_board_matrix();

        // اختار مجموعة الأرقام حسب اللاعب
        vector<int> available_numbers = (player->get_symbol() == 'X') ? odd_numbers : even_numbers;

        // احذف الأرقام المستخدمة بالفعل على اللوح
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                available_numbers.erase(
                    remove(available_numbers.begin(), available_numbers.end(), boardMatrix[i][j]),
                    available_numbers.end()
                );


        val = available_numbers[rand() % available_numbers.size()];


        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (boardMatrix[x][y] != 0);

        cout << player->get_name() << " played (" << x << ", " << y << ") with " << val << "\n";
    }

    return new Move<int>(x, y, val);
}

Player<int>* NumericalUI::create_player(std::string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}
