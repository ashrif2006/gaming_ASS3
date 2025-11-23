#include "sus.h"
#include <cctype>

SusBoard::SusBoard() : Board<char>(3,3) {
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
            board[i][j] = ' ';
}

bool SusBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char sym = move->get_symbol();
    int player_idx = current_player; 

    if(r<0 || r>=rows || c<0 || c>=columns || board[r][c] != ' ')
        return false;

    sym = toupper(sym);

    if (sym != 'S' && sym != 'U') {
        std::cout << "Invalid symbol. Please use S or U.\n";
        return false; 
    }

    board[r][c] = sym;

    int score_count = 0;

    if (c >= 2 && board[r][c-1] == 'U' && board[r][c-2] == 'S') score_count++;
    if (c <= columns - 3 && board[r][c+1] == 'U' && board[r][c+2] == 'S') score_count++;
    if (sym == 'U' && c > 0 && c < columns - 1 && board[r][c-1] == 'S' && board[r][c+1] == 'S') score_count++;

    if (r >= 2 && board[r-1][c] == 'U' && board[r-2][c] == 'S') score_count++;
    if (r <= rows - 3 && board[r+1][c] == 'U' && board[r+2][c] == 'S') score_count++;
    if (sym == 'U' && r > 0 && r < rows - 1 && board[r-1][c] == 'S' && board[r+1][c] == 'S') score_count++;
    
    player_scores[player_idx] += score_count;

    n_moves++;
    current_player = 1 - current_player;
    return true;
}



bool SusBoard::is_win(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }

    int idx = (player->get_symbol() == 'S') ? 0 : 1;
    int other = 1 - idx;
    return player_scores[idx] > player_scores[other];
}

bool SusBoard::is_lose(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }
    
    int idx = (player->get_symbol() == 'S') ? 0 : 1;
    int other = 1 - idx;
    return player_scores[idx] < player_scores[other];
}

bool SusBoard::is_draw(Player<char>* player) {
    return player_scores[0] == player_scores[1] && game_is_over(player);
}

bool SusBoard::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

int SusBoard::get_player_score(int index) const {
    return player_scores[index];
}

SusUI::SusUI(int cell_width) : UI<char>("S-U-S Game", cell_width) {}

Move<char>* SusUI::get_move(Player<char>* player) {
    int r, c;
    char sym;
    cout << player->get_name() << " move (row col symbol): ";
    cin >> r >> c >> sym;
    return new Move<char>(r,c,sym);
}

Player<char>* SusUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name,symbol,type);
}

Player<char>** SusUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    string name1,name2;
    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);

    players[0] = create_player(name1,'S', PlayerType::HUMAN);
    players[1] = create_player(name2,'U', PlayerType::HUMAN);

    return players;
}