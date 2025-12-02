#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <string>

class NumericalBoard : public Board<int> {
public:
    NumericalBoard();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

class NumericalUI : public UI<int> {
public:
    NumericalUI();
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(std::string& name, int symbol, PlayerType type) override;
};

#endif
