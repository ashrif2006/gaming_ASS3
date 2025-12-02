 #include <iostream>
#include "sus.h"                 //1
#include "FourInARow.h"          //2
#include "FiveByFiveTicTacToe.h" //3
#include "WordTicTacToe.h"       //4
#include "MisereTicTacToe.h"     //5
#include "DiamondTicTacToe.h"    //6
#include "FourByFourTicTacToe.h" //7
#include "PyramidTicTacToe.h"    //8
#include "NumericalTicTacToe.h"  //9
#include "ObstaclesTicTacToe.h"  //10
#include "FourByFourTicTacToe.h" // 7
#include "PyramidTicTacToe.h"    // 8
#include "sus.h"                 //1
#include "InfinityTicTacToe.h"   // 11
#include "FiveByFiveTicTacToe.h" // 9

#include "MemoryTicTacToe.h"     //13


using namespace std;

void menu()
{
    char op;
    do
    {
        cout << "Welcome To My World\n";
        cout << "\t1- S U S\n";
        cout << "\t2- Four In A Row\n";
        cout << "\t3- 5x5 Tic-Tac-Toe\n";
		cout << "\t4- Word Tic-Tac-Toe\n";
        cout << "\t5- Misere Tic-Tac-Toe\n";
        cout << "\t6- Diamond Tic-Tac-Toe\n";
        cout << "\t7- 4x4 Tic-Tac-Toe\n";
        cout << "\t8- Pyramid Tic-Tac-Toe\n";
        cout << "\t9- Numerical Tic-Tac-Toe\n";
        cout << "\t10- Obstacles Tic-Tac-Toe\n";
		cout << "\t11- Infinity Tic-Tac-Toe\n";
        cout << "\t12- Goodby\n";
        cout << "\t13- Exit\n";

        cout << "\t13- Memory Tic-Tac-Toe\n";
        cout << "\t14- Goodby\n";
        cout << "\t15- Exit\n";

        int choice;
        cout << "Please Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
         case 1:
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
        case 2:
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
        case 3:
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
        case 4:
        {
            WordBoard *board = new WordBoard();
            WordTicTacToeUI *ui = new WordTicTacToeUI();
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
        case 6:
        {
            DiamondBoard *board = new DiamondBoard();
            DiamondUI *ui = new DiamondUI();
            Player<char> **players = ui->setup_players();
            GameManager<char> gm(board, players, ui);
            gm.run();
            ui->display_final_results(board, players);
            delete board;
            delete ui;
            delete[] players;
            break;
        }
        case 7:
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
        case 8:
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
        case 9:
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
        
        case 10:
        {
            ObstaclesTicTacToeBoard *board = new ObstaclesTicTacToeBoard();
            ObstaclesTicTacToeUI *ui = new ObstaclesTicTacToeUI();
            Player<char> **players = ui->setup_players();

            // استخدم الـ GameManager العادي
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
        {}
        
        case 13:
        {
            MemoryBoard *board = new MemoryBoard();
            MemoryTicTacToeUI *ui = new MemoryTicTacToeUI();
            Player<char> **players = ui->setup_players();

            GameManager<char> gm(board, players, ui);
            gm.run();

            delete board;
            delete ui;
            delete[] players;
            break;
		}
        
        case 14:
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