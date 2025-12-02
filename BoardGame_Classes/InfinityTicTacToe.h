#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <queue>

class InfinityTicTacToe : public Board<char> {
private:
	std::queue<std::pair<int, int>> moves_history;


public:
    InfinityTicTacToe();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    
};

class InfinityTicTacToeUI : public UI<char> {
public:
    InfinityTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    
};

#endif