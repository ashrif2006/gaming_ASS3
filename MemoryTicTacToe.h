  #ifndef MEMORYTICTACTOE_H
#define MEMORYTICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>

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
    bool is_revealed(int row, int col) const;
    void reveal_position(int row, int col);
    
    // عرضين مختلفين: واحد للعب والتاني في النهاية
    void display_board() const;
    void display_final_board() const;
    
    char get_current_player() const;
    char get_cell(int row, int col) const;
};

class MemoryTicTacToeUI : public UI<char> {
public:
    MemoryTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& playerName, char playerSymbol, PlayerType playerType) override;
    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const;
};

#endif