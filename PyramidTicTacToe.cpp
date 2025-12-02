#include "PyramidTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

PyramidBoard::PyramidBoard() : Board<char>(3, 5) {
    // تهيئة اللوحة الهرمية
    board = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };
    
    // تعريف الخلايا الصالحة في الهرم
    valid_cells = {
        {false, false, true,  false, false},  // الصف 0: الخلية الوسطى فقط (قمة الهرم)
        {false, true,  false, true,  false},  // الصف 1: الخليتان على الجانبين
        {true,  false, true,  false, true}    // الصف 2: 3 خلايا (قاعدة الهرم)
    };
    
    n_moves = 0;
}

bool PyramidBoard::is_valid_cell(int x, int y) const {
    if (x < 0 || x >= 3 || y < 0 || y >= 5) {
        return false;
    }
    return valid_cells[x][y];
}

bool PyramidBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();
    
    // التحقق من أن الخلية صالحة وفارغة
    if (is_valid_cell(x, y) && board[x][y] == ' ') {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    
    return false;
}

bool PyramidBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    
    // تعريف جميع الخطوط الممكنة للفوز في الهرم
    
    // الخطوط الأفقية
    vector<vector<pair<int, int>>> winning_lines = {
        // الصف السفلي (القاعدة) - أفقي
        {{2, 0}, {2, 2}, {2, 4}},
        
        // الخطوط المائلة اليسرى
        {{2, 0}, {1, 1}, {0, 2}},  // مائل من أسفل يسار إلى أعلى
        {{2, 2}, {1, 1}, {0, 2}},  // مائل من الوسط إلى أعلى
        
        // الخطوط المائلة اليمنى
        {{2, 4}, {1, 3}, {0, 2}},  // مائل من أسفل يمين إلى أعلى
        {{2, 2}, {1, 3}, {0, 2}},  // مائل من الوسط إلى أعلى
        
        // الخطوط العمودية
        {{2, 0}, {1, 1}, {0, 2}},  // عمودي يسار
        {{2, 2}, {1, 1}, {0, 2}},  // عمودي وسط
        {{2, 4}, {1, 3}, {0, 2}}   // عمودي يمين
    };
    
    // التحقق من كل خط فوز محتمل
    for (const auto& line : winning_lines) {
        bool win = true;
        for (const auto& cell : line) {
            if (board[cell.first][cell.second] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    
    return false;
}

bool PyramidBoard::is_lose(Player<char>* player) {
    return false;
}

bool PyramidBoard::is_draw(Player<char>* player) {
    // التعادل عندما تمتلئ جميع الخلايا الصالحة ولا يوجد فائز
    int total_valid_cells = 0;
    int filled_cells = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (valid_cells[i][j]) {
                total_valid_cells++;
                if (board[i][j] != ' ') {
                    filled_cells++;
                }
            }
        }
    }
    
    return (filled_cells == total_valid_cells) && !is_win(player);
}

bool PyramidBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void PyramidBoard::display_pyramid() const {
    cout << "\nPyramid Board:\n";
    cout << "    " << board[0][2] << "    \n";
    cout << "  " << board[1][1] << "   " << board[1][3] << "  \n";
    cout << board[2][0] << "   " << board[2][2] << "   " << board[2][4] << "\n";
    cout << "Coordinates:\n";
    cout << "    (0,2)    \n";
    cout << "  (1,1) (1,3)  \n";
    cout << "(2,0) (2,2) (2,4)\n";
}

/////////////////////////////
//Pyramid UI
/////////////////////////////
PyramidUI::PyramidUI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe!", 3) {}

Move<char>* PyramidUI::get_move(Player<char>* player) {
    auto board_ptr = dynamic_cast<PyramidBoard*>(player->get_board_ptr());
    
    // عرض اللوحة الهرمية
    board_ptr->display_pyramid();
    
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "'s turn (symbol: " << player->get_symbol() << ")\n";
        
        while (true) {
            cout << "Enter coordinates for your move:\n";
            cout << "Available coordinates: (0,2), (1,1), (1,3), (2,0), (2,2), (2,4)\n";
            cout << "Enter row (0-2): ";
            cin >> x;
            cout << "Enter column (0-4): ";
            cin >> y;
            
            if (!board_ptr->is_valid_cell(x, y)) {
                cout << "Invalid coordinates! This is not a valid cell in the pyramid.\n";
                cout << "Valid coordinates are: (0,2), (1,1), (1,3), (2,0), (2,2), (2,4)\n";
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
        // كمبيوتر عشوائي
        vector<pair<int, int>> valid_moves;
        
        // جمع جميع الخلايا الصالحة والفارغة
        auto boardMatrix = player->get_board_ptr()->get_board_matrix();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (board_ptr->is_valid_cell(i, j) && boardMatrix[i][j] == ' ') {
                    valid_moves.push_back({i, j});
                }
            }
        }
        
        if (!valid_moves.empty()) {
            auto move = valid_moves[rand() % valid_moves.size()];
            x = move.first;
            y = move.second;
            cout << player->get_name() << " played (" << x << ", " << y << ")\n";
        } else {
            // إذا لم توجد حركات متاحة، استخدم خلية افتراضية
            x = 0; y = 2;
        }
    }
    
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* PyramidUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}