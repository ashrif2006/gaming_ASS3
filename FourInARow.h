#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H
/*
    المشكله 
    الأبعاد: 6 × 7.
    العلامات: كل لاعب لديه علامة خاصة به. عادةً ما تكون 'X' للاعب الأول و 'O' للاعب الثاني
    البداية: يبدأ اللاعب الأول بوضع علامته ('X') في أدنى مربع متاح في أي عمود يختاره.
    التناوب والحركة:

يتناوب اللاعبون على اللعب.

في كل دور، يختار اللاعب عمودًا من الأعمدة السبعة.

يضع اللاعب علامته في أدنى مربع فارغ (متاح) في ذلك العمود.

*/
#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <queue>

class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;


};

class FourInARowUI : public UI<char> {
public:
    FourInARowUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;


};

#endif