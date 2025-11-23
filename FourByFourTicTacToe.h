#ifndef FOURBYFOUR_TICTACTOE_H
#define FOURBYFOUR_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class FourByFourBoard : public Board<char> {
private:
    struct Piece {
        int x, y;
        char symbol;
        Piece(int x, int y, char s) : x(x), y(y), symbol(s) {}
    };
    
    std::vector<Piece> pieces;  // جميع القطع على اللوحة
    char current_player_symbol;

public:
    FourByFourBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    // دالة مساعدة للتحقق من الحركة القانونية
    bool is_valid_move(int from_x, int from_y, int to_x, int to_y, char symbol);
    
    // دالة للعثور على قطعة في موقع معين
    int find_piece_index(int x, int y);
    
    // دالة لتحريك قطعة
    bool move_piece(int from_x, int from_y, int to_x, int to_y, char symbol);
};

class FourByFourUI : public UI<char> {
public:
    FourByFourUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    
    // دالة مساعدة للحصول على حركة معقدة (من-إلى)
    Move<char>* get_complex_move(Player<char>* player);
};

#endif