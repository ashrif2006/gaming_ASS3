#ifndef MEMORYTICTACTOE_H
#define MEMORYTICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <memory>

class MemoryBoard : public Board<char> {
private:
	std::vector<std::vector<bool>> revealed;
    char currentPlayer;

public:
    MemoryBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

	void reveal_all();
	void hide_all();
	bool is_revealed(int x, int y) const;
	void reveal_position(int x, int y);
	void display_memory_board() const;
    char get_current_player() const { return currentPlayer; }
};

class MemoryTicTacToeUI : public UI<char> {
public:
    MemoryTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif
