/*
            SusBoard *board = new SusBoard();
            SusUI *ui = new SusUI();
            Player<char> **players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();
            cout << "\nFinal Scores:\n";
            for (int i = 0; i < 2; i++)
            {
                cout << players[i]->get_name() << ": "
                     << board->get_player_score(i) << " points\n";
            }
  
            if (board->is_win(players[0]))
                cout << players[0]->get_name() << " wins!\n";
            else if (board->is_win(players[1]))
                cout << players[1]->get_name() << " wins!\n";
            else
                cout << "Draw!\n";

            delete board;
            delete ui;
            delete[] players;
            break;

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
};

#endif
