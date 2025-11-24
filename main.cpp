#include <iostream>
#include "NumericalTicTacToe.h"
#include "MisereTicTacToe.h"     //5
#include "FourByFourTicTacToe.h" // 7
#include "PyramidTicTacToe.h"    // 8
#include "sus.h"                 //1
#include "InfinityTicTacToe.h"   // 11
#include "FiveByFiveTicTacToe.h" // 3

using namespace std;

void menu()
{
    char op;
    do
    {
        cout << "Welcome To My World\n";
        cout << "\t1- Numerical Tic-Tac-Toe\n";
        cout << "\t2- Misere Tic-Tac-Toe\n";
        cout << "\t3- 4x4 Tic-Tac-Toe\n";
        cout << "\t4- Pyramid Tic-Tac-Toe\n";
        cout << "\t5- S U S\n";
        cout << "\t6- 5x5 Tic-Tac-Toe\n";
		cout << "\t11- Infinity Tic-Tac-Toe\n";
        cout << "\t7- Goodby\n";
        cout << "\t8- Exit\n";

        int choice;
        cout << "Please Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            NumericalBoard *board = new NumericalBoard();
            NumericalUI *ui = new NumericalUI();
            Player<int> **players = ui->setup_players();

            GameManager<int> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 2:
        {
            MisereBoard *board = new MisereBoard();
            MisereUI *ui = new MisereUI();
            Player<char> **players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 3:
        {
            FourByFourBoard *board = new FourByFourBoard();
            FourByFourUI *ui = new FourByFourUI();
            Player<char> **players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 4:
        {
            PyramidBoard *board = new PyramidBoard();
            PyramidUI *ui = new PyramidUI();
            Player<char> **players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 5:
        {
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
        }
        case 6:
        {
            FiveByFiveBoard* board = new FiveByFiveBoard();
            FiveByFiveUI* ui = new FiveByFiveUI();
            Player<char>** players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 11:
        {
            InfinityTicTacToe *board = new InfinityTicTacToe();
            InfinityTicTacToeUI *ui = new InfinityTicTacToeUI();
            Player<char> **players = ui->setup_players();
            GameManager<char> gm(board, players, ui);
            gm.run();
            delete board;
            delete ui;
            delete[] players;
            break;
		}
        case 7:
        {
            cout << "Goodbye!\n";
            return;
        }
        default:
            cout << "Game not implemented yet.\n";
        }

        cout << "Do you want to play again? Y/N: ";
        cin >> op;

    } while (op == 'y' || op == 'Y');
}

int main()
{
    menu();
    return 0;
}