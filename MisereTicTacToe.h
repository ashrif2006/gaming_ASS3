 #ifndef MISERE_TICTACTOE_H
#define MISERE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class MisereBoard : public Board<char> {
private:
    int n_moves;
public:
    MisereBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    // إزالة override لأن الدالة غير موجودة في الكلاس الأساسي
    void display_board();
};

class MisereUI : public UI<char> {
public:
    MisereUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif