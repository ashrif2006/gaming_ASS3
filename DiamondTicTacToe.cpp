 #include "DiamondTicTacToe.h"
#include <iomanip>
#include <limits>

DiamondBoard::DiamondBoard() : Board<char>(5, 5), currentPlayer('X') {
    // نعمل الشكل الماسي - بنحط '.' في الخلايا الي مش فعالة
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 && j != 2) || (i == 1 && (j < 1 || j > 3)) || (i == 3 && (j < 1 || j > 3)) || (i == 4 && j != 2)) {
                board[i][j] = '.';  // خلية مش فعالة
            } else {
                board[i][j] = ' ';  // خلية فعالة وفاضية
            }
        }
    }
}

bool DiamondBoard::is_valid_position(int row, int col) const {
    // نتأكد إن الإحداثيات within range وإن الخلية مش '.' 
    if (row < 0 || row >= 5 || col < 0 || col >= 5) {
        return false;
    }
    return board[row][col] != '.';
}

bool DiamondBoard::update_board(Move<char>* move) {
    int row = move->get_x();
    int col = move->get_y();
    char symbol = move->get_symbol();
    
    // نتأكد إن المكان صح وفاضي
    if (!is_valid_position(row, col) || board[row][col] != ' ') {
        delete move;
        return false;
    }
    
    board[row][col] = symbol;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    n_moves++;
    delete move;
    return true;
}

bool DiamondBoard::check_line(int startRow, int startCol, int deltaRow, int deltaCol, int length, char player) const {
    // نتحقق من خط بطول معين في اتجاه معين
    for (int i = 0; i < length; i++) {
        int row = startRow + i * deltaRow;
        int col = startCol + i * deltaCol;
        
        if (row < 0 || row >= 5 || col < 0 || col >= 5 || board[row][col] != player) {
            return false;
        }
    }
    return true;
}

bool DiamondBoard::check_three_in_line(char player) const {
    // نتحقق من كل الخطوط الممكنة طولها 3
    vector<pair<int, int>> directions = {
        {0, 1},   // أفقي
        {1, 0},   // رأسي  
        {1, 1},   // قطري
        {1, -1}   // قطري عكسي
    };
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!is_valid_position(i, j)) continue;
            
            for (auto& dir : directions) {
                if (check_line(i, j, dir.first, dir.second, 3, player)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool DiamondBoard::check_four_in_line(char player) const {
    // نتحقق من الخطوط الأفقية
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 1; j++) {
            if (check_line(i, j, 0, 1, 4, player)) return true;
        }
    }
    
    // نتحقق من الخطوط الرأسية  
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i <= 1; i++) {
            if (check_line(i, j, 1, 0, 4, player)) return true;
        }
    }
    
    // نتحقق من الخطوط القطرية
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (check_line(i, j, 1, 1, 4, player)) return true;
        }
    }
    
    // نتحقق من الخطوط القطرية العكسية
    for (int i = 0; i <= 1; i++) {
        for (int j = 3; j <= 4; j++) {
            if (check_line(i, j, 1, -1, 4, player)) return true;
        }
    }
    
    return false;
}

bool DiamondBoard::is_win(Player<char>* player) {
 // شرط الفوز: لازم يكون عندك خط 3 وخط 4 في نفس الوقت
    char symbol = player->get_symbol();
    return check_three_in_line(symbol) && check_four_in_line(symbol);
}

bool DiamondBoard::is_lose(Player<char>* player) {
    // لو الخصم كسب، يبقى انت خسرت
    char opponentSymbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    return check_three_in_line(opponentSymbol) && check_four_in_line(opponentSymbol);
}

bool DiamondBoard::is_draw(Player<char>* player) {
    // نتأكد إن اللوحة مليانة ومفيش حد كسب
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return !is_win(player) && !is_lose(player);
}

bool DiamondBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

// DiamondUI implementation
DiamondUI::DiamondUI() : UI<char>("=== Diamond Tic-Tac-Toe ===", 3) {}

Move<char>* DiamondUI::get_move(Player<char>* player) {
    int row, col;
    bool valid_input = false;
    
    while (!valid_input) {
        cout << player->get_name() << "'s turn (symbol: " << player->get_symbol() << ")\n";
        cout << "Enter row (0-4): ";
        
        if (cin >> row) {
            cout << "Enter column (0-4): ";
            if (cin >> col) {
                valid_input = true;
            }
        }
        
        if (!valid_input) {
            cout << "Invalid input! Please enter numbers only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* DiamondUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void DiamondUI::display_final_results(Board<char>* board, Player<char>* players[2]) {
    cout << "\n=== Game Over ===\n";
    
    // Display final board
    display_board_matrix(board->get_board_matrix());
    
    for (int i = 0; i < 2; i++) {
        if (board->is_win(players[i])) {
            cout << "Winner: " << players[i]->get_name() << "\n";
            return;
        }
    }
    
    if (board->is_draw(players[0])) {
        cout << "It's a draw!\n";
    }
}