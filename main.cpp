#include <iostream>
#include "NumericalTicTacToe.h"

using namespace std;

void menu() {
    char op;
    do {
        cout << "Welcome To My World\n";
        cout << "\t1- Numerical Tic-Tac-Toe\n";
        cout << "\t2- Game2\n";

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
