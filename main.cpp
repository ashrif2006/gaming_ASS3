 #include <iostream>
#include "NumericalTicTacToe.h"
#include "MisereTicTacToe.h" //5

using namespace std;

void menu() {
    char op;
    do {
        cout << "Welcome To My World\n";
        cout << "\t1- Numerical Tic-Tac-Toe\n";
        cout << "\t2- Misere Tic-Tac-Toe\n";
        cout << "\t3- Game2\n";
        cout << "\t4- Exit\n";

        int choice;
        cout << "Please Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                NumericalBoard* board = new NumericalBoard();
                NumericalUI* ui = new NumericalUI();
                Player<int>** players = ui->setup_players();

                GameManager<int> gm(board, players, ui);
                gm.run();

                delete board;
                delete ui;
                delete[] players;
                break;
            }
             case 2: {
                MisereBoard* board = new MisereBoard();
                MisereUI* ui = new MisereUI();
                Player<char>** players = ui->setup_players();

                GameManager<char> gm(board, players, ui);
                gm.run();

                delete board;
                delete ui;
                delete[] players;
                break;
            }
            case 3: {
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

int main() {
    menu();
    return 0;
}