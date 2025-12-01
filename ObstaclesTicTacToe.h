 #ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

class ObstaclesTicTacToeBoard : public Board<char> {
private:
    int roundCount;
public:
    ObstaclesTicTacToeBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class ObstaclesTicTacToeUI : public UI<char> {
public:
    ObstaclesTicTacToeUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

// استخدم الـ GameManager العادي بدل الـ ObstaclesGameManager
// لا داعي لـ derived class

#endif