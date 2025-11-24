#ifndef FOURBYFOUR_TICTACTOE_H
#define FOURBYFOUR_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <utility>

class FourByFourBoard : public Board<char> {
public:
    FourByFourBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // دالة مساعدة للتحقق من الحركة
    bool is_valid_move(int from_x, int from_y, int to_x, int to_y, char symbol) const;

    // دالة لتحريك القطعة مباشرة
    bool move_piece(int from_x, int from_y, int to_x, int to_y, char symbol);
};

class FourByFourUI : public UI<char> {
public:
    FourByFourUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif