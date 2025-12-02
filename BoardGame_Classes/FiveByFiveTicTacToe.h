#ifndef FIVEBYFIVE_TICTACTOE_H
#define FIVEBYFIVE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class FiveByFiveBoard : public Board<char> {
private:
    char currentPlayer;

public:
    FiveByFiveBoard();

    // Virtual functions from Board<char> 
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // custom functions
    int count_three_in_row(char symbol);
    int get_move_count() const { return n_moves; }
    char get_current_player() const { return currentPlayer; }
    char get_cell(int x, int y) const { return board[x][y]; }
};

class FiveByFiveUI : public UI<char> {
public:
    FiveByFiveUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};
#endif