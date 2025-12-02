  #include "MemoryTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

MemoryBoard::MemoryBoard() : Board<char>(3, 3), currentPlayer('X') {
    board = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    revealed = {{false,false,false},{false,false,false},{false,false,false}};
}

bool MemoryBoard::update_board(Move<char>* move) {
    int row = move->get_x();
    int col = move->get_y();
    char symbol = move->get_symbol();
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') 
        return false;
    board[row][col] = symbol;
    n_moves++;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

bool MemoryBoard::is_win(Player<char>* player) {
    char s = player->get_symbol();
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == s && board[i][1] == s && board[i][2] == s) 
            return true;
        if(board[0][i] == s && board[1][i] == s && board[2][i] == s) 
            return true;
    }
    if(board[0][0] == s && board[1][1] == s && board[2][2] == s) 
        return true;
    if(board[0][2] == s && board[1][1] == s && board[2][0] == s) 
        return true;
    return false;
}

bool MemoryBoard::is_lose(Player<char>* player) {
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> temp("", opp, PlayerType::HUMAN);
    return is_win(&temp);
}

bool MemoryBoard::is_draw(Player<char>* player) {
    return (n_moves >= 9) && !is_win(player) && !is_lose(player);
}

bool MemoryBoard::game_is_over(Player<char>* player) {
    bool over = is_win(player) || is_lose(player) || is_draw(player);
    if(over) { 
        reveal_all(); 
        display_final_board(); 
    }
    return over;
}

void MemoryBoard::reveal_all() {
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++) 
            revealed[i][j] = true;
}

void MemoryBoard::hide_all() {
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++) 
            revealed[i][j] = false;
}

bool MemoryBoard::is_revealed(int r, int c) const {
    return (r >= 0 && r < 3 && c >= 0 && c < 3) ? revealed[r][c] : false;
}

void MemoryBoard::reveal_position(int r, int c) {
    if(r >= 0 && r < 3 && c >= 0 && c < 3) 
        revealed[r][c] = true;
}

void MemoryBoard::display_board() const {
    cout << "\nCurrent Memory Board:\n" ;
    cout <<"  0   1   2\n ";
     cout <<"-------------\n";
    for(int r = 0; r < 3; r++) {
        cout << r << " "; 
        for(int c = 0; c < 3; c++) 
            cout << "| ? "; 
        cout << "|\n";
        if(r < 2) 
            cout << "  -------------\n";
    }
    cout << "  -------------\n\n";
}

void MemoryBoard::display_final_board() const {
    cout << "\n=== FINAL RESULT ===\n";
     cout<<"  0   1   2\n";
     cout<<"  -------------\n";
    for(int r = 0; r < 3; r++) {
        cout << r << " "; 
        for(int c = 0; c < 3; c++) {
            cout << "| " << (board[r][c] == ' ' ? ' ' : board[r][c]) << " ";
        } 
        cout << "|\n"; 
        if(r < 2) 
            cout << "  -------------\n";
    }
    cout << "  -------------\n\n";
}

char MemoryBoard::get_current_player() const { 
    return currentPlayer; 
}

char MemoryBoard::get_cell(int r, int c) const {
    return (r >= 0 && r < 3 && c >= 0 && c < 3) ? board[r][c] : ' ';
}

/////////////////////////////
// Memory UI
/////////////////////////////
MemoryTicTacToeUI::MemoryTicTacToeUI() : UI<char>("Memory Tic-Tac-Toe", 3) {}

Move<char>* MemoryTicTacToeUI::get_move(Player<char>* player) {
    char sym = player->get_symbol();
    auto board_ptr = dynamic_cast<MemoryBoard*>(player->get_board_ptr());

    if(player->get_type() == PlayerType::HUMAN) {
        int r, c; 
        cout << "\n" << player->get_name() << " (" << sym << ") turn:\n";
        board_ptr->display_board();
        while(1) {
            cout << "Enter row col (0-2): "; 
            cin >> r >> c;
            if(cin.fail()) {
                cin.clear(); 
                cin.ignore(1000, '\n'); 
                cout << "Invalid!\n"; 
                continue;
            }
            if(r < 0 || r > 2 || c < 0 || c > 2) {
                cout << "0-2 only!\n"; 
                continue;
            }
            if(board_ptr->get_cell(r, c) != ' ') {
                cout << "Taken!\n"; 
                continue;
            }
            break;
        }
        return new Move<char>(r, c, sym);
    } else {
        vector<pair<int, int>> empty;
        for(int i = 0; i < 3; i++) 
            for(int j = 0; j < 3; j++)
                if(board_ptr->get_cell(i, j) == ' ') 
                    empty.push_back({i, j});
        if(empty.empty()) 
            return new Move<char>(0, 0, sym);
        int idx = rand() % empty.size();
        int r = empty[idx].first, c = empty[idx].second;
        cout << player->get_name() << " chooses (" << r << "," << c << ")\n";
        return new Move<char>(r, c, sym);
    }
}

Player<char>* MemoryTicTacToeUI::create_player(string& n, char s, PlayerType t) {
    return new Player<char>(n, s, t);
}

void MemoryTicTacToeUI::display_board_matrix(const vector<vector<char>>& m) const {
    cout << "\n";
}