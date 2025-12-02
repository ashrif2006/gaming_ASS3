 #include "DiamondTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

DiamondBoard::DiamondBoard() : Board<char>(5, 5), currentPlayer('X') {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 && j != 2) ||  (i == 1 && (j < 1 || j > 3)) ||  (i == 3 && (j < 1 || j > 3)) ||  (i == 4 && j != 2)) {
                board[i][j] = '.';  // خلية غير فعالة
            } else {
                board[i][j] = ' ';  // خلية فعالة
            }
        }
    }
}
bool DiamondBoard::is_valid_position(int row, int col) const {
    if (row < 0 || row >= 5 || col < 0 || col >= 5) return false;
    return board[row][col] != '.';
}
bool DiamondBoard::update_board(Move<char>* move) {
    int row = move->get_x();
    int col = move->get_y();
    char symbol = move->get_symbol();
    
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

bool DiamondBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    
    // نتحقق من خط 3 و خط 4 في نفس الوقت
    bool has_three = false;
    bool has_four = false;
    
    // اتجاهات الخطوط
    int dirs[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    
    // نتحقق من كل الخطوط الممكنة
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!is_valid_position(i, j)) continue;
            
            for (auto& dir : dirs) {
                int dr = dir[0], dc = dir[1];
                
                // تحقق من خط طوله 3
                if (i + 2*dr < 5 && j + 2*dc < 5 && j + 2*dc >= 0) {
                    if (board[i][j] == symbol && 
                        board[i+dr][j+dc] == symbol && 
                        board[i+2*dr][j+2*dc] == symbol) {
                        has_three = true;
                    }
                }
                
                // تحقق من خط طوله 4  
                if (i + 3*dr < 5 && j + 3*dc < 5 && j + 3*dc >= 0) {
                    if (board[i][j] == symbol && 
                        board[i+dr][j+dc] == symbol && 
                        board[i+2*dr][j+2*dc] == symbol &&
                        board[i+3*dr][j+3*dc] == symbol) {
                        has_four = true;
                    }
                }
            }
        }
    }
    
    return has_three && has_four;
}

bool DiamondBoard::is_lose(Player<char>* player) {
    char opponent = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> temp("temp", opponent, PlayerType::HUMAN);
    return is_win(&temp);
}

bool DiamondBoard::is_draw(Player<char>* player) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return !is_win(player) && !is_lose(player);
}

bool DiamondBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}


/////////////////////////////
//Diamond UI
/////////////////////////////
DiamondUI::DiamondUI() : UI<char>("=== Diamond Tic-Tac-Toe ===", 3) {}

Player<char>** DiamondUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Move<char>* DiamondUI::get_move(Player<char>* player) {
    int row, col;
    
    if (player->get_type() == PlayerType::COMPUTER) {
        // حركة الكمبيوتر
        srand(time(0));
        Board<char>* gameBoard = player->get_board_ptr();
        vector<vector<char>> currentBoard = gameBoard->get_board_matrix();
        
        do {
            row = rand() % 5;
            col = rand() % 5;
        } while (!dynamic_cast<DiamondBoard*>(gameBoard)->is_valid_position(row, col) || 
                 currentBoard[row][col] != ' ');
        cout << "Computer plays at (" << row << ", " << col << ")\n";
    } else {
        // حركة الإنسان
        cout << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter row and column (0-4): ";
        cin >> row >> col;
    }
    
    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* DiamondUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void DiamondUI::display_final_results(Board<char>* board, Player<char>* players[2]) {
    cout << "\n=== Game Over ===\n";
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