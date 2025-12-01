#ifndef DIAMONDTICTACTOE_H
#define DIAMONDTICTACTOE_H

#include "BoardGame_Classes.h"

class DiamondBoard : public Board<char> {
private:
    char currentPlayer;
    
public:
    DiamondBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    bool is_valid_position(int row, int col) const;
};

class DiamondUI : public UI<char> {
public:
    DiamondUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
    void display_final_results(Board<char>* board, Player<char>* players[2]);
};

#endif