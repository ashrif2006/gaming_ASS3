#include "WordTicTacToe.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

WordBoard::WordBoard() : Board<char>(3, 3), currentPlayer('X') , dictLoaded(false){
    board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    if (!load_dictionary("dic.txt")) {
        cout << "Could not load dictionary file. we could use deafult words. \n ";

        dictionary = { "CAT" , "DOG", "SUN" , "CAR" , "EGG", "BED", "HAT", "FLY", "ICE" };
        dictLoaded = true;
    }
}

bool WordBoard::load_dictionary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false; // Return false if the file cannot be opened
    }

    string word;
    // Read ALL words from the file until the end
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3) {
            dictionary.insert(word);
        }

        file.close();
        dictLoaded = true;
        return true;
    }
   
}

bool WordBoard::is_valid_word(const string& word) {
    if (word.length() != 3) return false;
    for (char c : word) {
        if (c == ' ') return false;
    }
    string upper_word = word;
    transform(upper_word.begin(), upper_word.end(), upper_word.begin(), ::toupper);
    return dictionary.find(upper_word) != dictionary.end();
}

bool WordBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

bool WordBoard::checkAllWords() {

    //check horizontally
    for(int i = 0; i < 3; i++) {
        string word = "";
        word += board[i][0];
        word += board[i][1];
        word += board[i][2];
        if (word[0] != ' ' && word[1] != ' ' && word[2] != ' ') {
            if (is_valid_word(word)) {
                return true;
            }
        }
    }

    //check vertically
    for (int j = 0; j < 3; j++) {
        string word = "";
        word += board[0][j];
        word += board[1][j];
        word += board[2][j];
        if (word[0] != ' ' && word[1] != ' ' && word[2] != ' ') {
            if (is_valid_word(word)) {
                return true;
            }
        }
    }
    // check diagonally 
    string word1, word2;
    for(int i =0; i < 3; i++) {
        word1 += board[i][i];
        word2 += board[i][2 - i];
	}
	//return (word1[0] != ' ' && is_valid_word(word1)) || (word2[0] != ' ' && is_valid_word(word2));
    if (is_valid_word(word1)) return true;
    if (is_valid_word(word2)) return true;

    return false;
}

bool WordBoard::is_win(Player<char>* player) {
    return checkAllWords();
}

bool WordBoard::is_lose(Player<char>* player) {
    if (checkAllWords()) {
        return true;
    }
    return false;
}

bool WordBoard::is_draw(Player<char>* player) {
    return (n_moves >= 9) &&  !checkAllWords();
}

bool WordBoard::game_is_over(Player<char>* player) {
    return checkAllWords() || (n_moves >=9);
}

/////////////////////////////
// Word UI
/////////////////////////////

WordTicTacToeUI::WordTicTacToeUI() : UI<char>("Welcome to Word Tic-Tac-Toe!", 4) {}

Move<char>* WordTicTacToeUI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();  // Fixed: add parentheses
    auto board_ptr = dynamic_cast<WordBoard*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        char letter;  // Fixed: declare letter variable

        while (true) {
            cout << "\n" << player->get_name() << "'s turn (symbol: " << symbol << ")\n";

            // Display available moves
            cout << "Current Board:\n";
            vector<vector<char>> board_matrix = board_ptr->get_board_matrix();
            display_board_matrix(board_matrix);

            cout << "Available positions: ";
            bool first = true;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board_matrix[i][j] == ' ') {
                        if (!first) cout << ", ";
                        cout << "(" << i << "," << j << ")";
                        first = false;
                    }
                }
            }
            cout << endl;

            cout << "Enter position (row): ";
            cin >> x;
			cout << "Enterposition (column): ";
			cin >> y;

            if (x < 0 || x >= 3 || y < 0 || y >= 3) {
                cout << "Invalid coordinates! Please enter numbers between 0 and 2.\n";
                continue;
            }

            if (board_matrix[x][y] != ' ') {
                cout << "That position is already taken! Please choose an empty cell.\n";
                continue;
            }

            cout << "Enter letter to place: ";
            cin >> letter;
            letter = toupper(letter); // Convert to uppercase

            if (letter < 'A' || letter > 'Z') {
                cout << "Invalid letter! Please enter a letter from A to Z.\n";
                continue;
            }

            break;
        }
        return new Move<char>(x, y, letter);
    }
    else {
        // Computer player - random move with random letter
        vector<pair<int, int>> empty_cells;

        // Find all empty cells
        auto board_matrix = board_ptr->get_board_matrix();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board_matrix[i][j] == ' ') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (!empty_cells.empty()) {
            auto move_pos = empty_cells[rand() % empty_cells.size()];
            char random_letter = 'A' + (rand() % 26); // Random letter A-Z
            cout << player->get_name() << " (Computer) places '" << random_letter
                << "' at position (" << move_pos.first << "," << move_pos.second << ")\n";
            return new Move<char>(move_pos.first, move_pos.second, random_letter);
        }

        return new Move<char>(0, 0, 'A');
    }
}

Player<char>* WordTicTacToeUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}