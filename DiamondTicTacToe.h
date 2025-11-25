 #ifndef DIAMONDTICTACTOE_H
#define DIAMONDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

using namespace std;

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
    
    // Helper functions
    bool is_valid_position(int row, int col) const;
    bool check_line(int startRow, int startCol, int deltaRow, int deltaCol, int length, char player) const;
    bool check_three_in_line(char player) const;
    bool check_four_in_line(char player) const;
};

class DiamondUI : public UI<char> {
public:
    DiamondUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    void display_final_results(Board<char>* board, Player<char>* players[2]);
};

#endif