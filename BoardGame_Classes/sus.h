/*
* المشكله 
            SUS
 Introduction: A game on a 3x3 grid where the objective is to form the sequence "S-U-S".  Board: A 3x3 grid.  Rules: Players take turns placing either an "S" or a "U" in an empty square. A player must use the same
letter each turn. A player scores a point for each "S-U-S" sequence they create.  Winning Condition: The game ends when the board is full. The player who has created the most "S-U-S"
sequences wins.

*/

#ifndef SUS_H
#define SUS_H

#include <iostream>
#include <vector>
#include <string>
#include "BoardGame_Classes.h"

using namespace std;

class SusBoard : public Board<char> {
private:
    int player_scores[2] = {0, 0};
    vector<pair<int,int>> s_positions[2]; 
    int current_player = 0;

public:
    SusBoard();

    bool update_board(Move<char>* move) override;  

    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int get_player_score(int index) const;
};

class SusUI : public UI<char> {
public:
    SusUI(int cell_width = 5);

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Player<char>** setup_players() override;
	//داله لعرض النتائج النهائيه
    void display_final_results(Board<char>* board, Player<char>** players);
};

#endif
