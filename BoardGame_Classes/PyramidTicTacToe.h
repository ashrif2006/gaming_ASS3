#ifndef PYRAMID_TICTACTOE_H
#define PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class PyramidBoard : public Board<char> {
private:
    // تمثيل اللوحة الهرمية (3 صفوف، 5 أعمدة مع خلايا غير مستخدمة)
    std::vector<std::vector<bool>> valid_cells; // الخلايا الصالحة للعب
    
public:
    PyramidBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    // التحقق إذا كانت الخلية صالحة في الهرم
    bool is_valid_cell(int x, int y) const;
    
    // عرض اللوحة الهرمية بشكل خاص
    void display_pyramid() const;
};

class PyramidUI : public UI<char> {
public:
    PyramidUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif