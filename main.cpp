#include <iostream>
#include "NumericalTicTacToe.h"
#include "sus.h"                 //1
#include "FourInARow.h"           //2
#include"FiveByFiveTicTacToe.h" //3
#include "WordTicTacToe.h"   //4
#include "MisereTicTacToe.h"     //5
#include "FourByFourTicTacToe.h" // 7
#include "PyramidTicTacToe.h"    // 8
#include "InfinityTicTacToe.h"   // 11
#include "MemoryTicTacToe.h"     //13

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
		cout << "\t6- Four In A Row\n";
        cout << "\t7- 5x5 Tic-Tac-Toe\n";
        cout << "\t8- Word Tic-Tac-Toe\n";
		cout << "\t11- Infinity Tic-Tac-Toe\n";
        cout << "\t12- Memory Tic-Tac-Toe (Bonus)\n";
        cout << "\t13- Goodby\n";
        cout << "\t14- Exit\n";

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
            ui->display_final_results(board, players);
            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 6: 
        {
            FourInARowBoard *board = new FourInARowBoard();
            FourInARowUI *ui = new FourInARowUI();
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

        case 8: 
        {
            WordBoard* board = new WordBoard();
            WordTicTacToeUI* ui = new WordTicTacToeUI();
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
        case 12:
        {
            MemoryBoard* board = new MemoryBoard();
            MemoryTicTacToeUI* ui = new MemoryTicTacToeUI();
            Player<char>** players = ui->setup_players();
            GameManager<char> gm(board, players, ui);
            gm.run();
            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 13:
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