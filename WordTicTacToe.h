#ifndef WORDTICTACTOE_H
#define WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <unordered_set>

class WordBoard : public Board<char> {
private:
	char currentPlayer;
    std::unordered_set<std::string>dictionary;
	bool dictLoaded;

public:
	WordBoard();

	bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // Word game specific functions
    bool load_dictionary(const std::string& filename);
    bool is_valid_word(const std::string& word);
    bool checkAllWords();
    char get_current_player() const { return currentPlayer; }
    bool is_dict_loaded() const { return dictLoaded; }
};

class WordTicTacToeUI : public UI<char> {
public:
    WordTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif