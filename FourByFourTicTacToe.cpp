#include "FourByFourTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

FourByFourBoard::FourByFourBoard() : Board<char>(4, 4) {
    // المواقع الأولية الثابتة
    board = {
        {'O', 'X', 'O', 'X'},  // الصف 0
        {' ', ' ', ' ', ' '},   // الصف 1  
        {' ', ' ', ' ', ' '},   // الصف 2
        {'X', 'O', 'X', 'O'}    // الصف 3
    };
    n_moves = 0;
}

bool FourByFourBoard::is_valid_move(int from_x, int from_y, int to_x, int to_y, char symbol) const {
    // تحقق من الإحداثيات
    if (from_x < 0 || from_x >= 4 || from_y < 0 || from_y >= 4) return false;
    if (to_x < 0 || to_x >= 4 || to_y < 0 || to_y >= 4) return false;

    // تحقق من أن القطعة الأصلية تخص اللاعب
    if (board[from_x][from_y] != symbol) return false;

    // تحقق من أن الهدف فارغ
    if (board[to_x][to_y] != ' ') return false;

    // تحقق من أن الحركة مجاورة (أفقي أو عمودي فقط)
    int dx = abs(to_x - from_x);
    int dy = abs(to_y - from_y);
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

bool FourByFourBoard::move_piece(int from_x, int from_y, int to_x, int to_y, char symbol) {
    if (!is_valid_move(from_x, from_y, to_x, to_y, symbol)) {
        return false;
    }

    // نفذ الحركة
    board[from_x][from_y] = ' ';
    board[to_x][to_y] = symbol;
    n_moves++;

    return true;
}

bool FourByFourBoard::update_board(Move<char>* move) {
    // في هذه النسخة، نستخدم move->get_x() و move->get_y() كإحداثيات الهدف
    // ونبحث عن قطعة يمكن تحريكها إلى هناك

    int to_x = move->get_x();
    int to_y = move->get_y();
    char symbol = move->get_symbol();

    // البحث عن قطعة يمكن تحريكها إلى الهدف
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == symbol && is_valid_move(i, j, to_x, to_y, symbol)) {
                return move_piece(i, j, to_x, to_y, symbol);
            }
        }
    }
    return false;
}

bool FourByFourBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    // تحقق من الصفوف - 3 متتالية
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                return true;
            }
        }
    }

    // تحقق من الأعمدة - 3 متتالية
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                return true;
            }
        }
    }

    // تحقق من الأقطار - 3 متتالية
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                return true;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 2; j < 4; j++) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                return true;
            }
        }
    }

    return false;
}

bool FourByFourBoard::is_lose(Player<char>* player) {
    return false;
}

bool FourByFourBoard::is_draw(Player<char>* player) {
    return n_moves >= 20 && !is_win(player);
}

bool FourByFourBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/////////////////////////////
//FourByFour UI
/////////////////////////////
FourByFourUI::FourByFourUI() : UI<char>("4x4 Tic-Tac-Toe - Move your tokens to make 3 in a row!", 3) {}

Move<char>* FourByFourUI::get_move(Player<char>* player) {
    FourByFourBoard* board_ptr = (FourByFourBoard*)player->get_board_ptr();
    char symbol = player->get_symbol();
    int from_x, from_y, to_x, to_y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << symbol << ")\n";

        // عرض اللوحة الحالية
        display_board_matrix(player->get_board_ptr()->get_board_matrix());

        // عرض القواعد
        cout << "Rules: Move your tokens to adjacent empty cells (horizontal/vertical only)\n";
        cout << "Win by making 3 of your tokens in a row!\n\n";

        while (true) {
            // الخطوة 1: اختيار القطعة المراد تحريكها
            cout << "Step 1 - Choose which token to move:\n";

            // عرض قطع اللاعب الحالية
            vector<pair<int, int>> player_tokens;
            auto boardMatrix = player->get_board_ptr()->get_board_matrix();
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (boardMatrix[i][j] == symbol) {
                        player_tokens.push_back({ i, j });
                        cout << "(" << i << "," << j << ") ";
                    }
                }
            }
            cout << endl;

            cout << "Enter token coordinates (row column): ";
            cin >> from_x >> from_y;

            // تحقق من أن القطعة تخص اللاعب
            bool valid_token = false;
            for (auto token : player_tokens) {
                if (token.first == from_x && token.second == from_y) {
                    valid_token = true;
                    break;
                }
            }

            if (!valid_token) {
                cout << "This is not your token! Choose from your tokens listed above.\n";
                continue;
            }

            // الخطوة 2: اختيار الوجهة
            cout << "Step 2 - Choose destination:\n";
            cout << "Available adjacent moves: ";

            vector<pair<int, int>> valid_destinations;
            // تحقق من جميع الاتجاهات الأربعة
            int directions[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // أعلى، أسفل، يسار، يمين

            for (auto dir : directions) {
                int nx = from_x + dir[0];
                int ny = from_y + dir[1];
                if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && boardMatrix[nx][ny] == ' ') {
                    valid_destinations.push_back({ nx, ny });
                    cout << "(" << nx << "," << ny << ") ";
                }
            }
            cout << endl;

            if (valid_destinations.empty()) {
                cout << "No valid moves from this token! Choose another token.\n";
                continue;
            }

            cout << "Enter destination coordinates (row column): ";
            cin >> to_x >> to_y;

            // تحقق من أن الوجهة صالحة
            bool valid_dest = false;
            for (auto dest : valid_destinations) {
                if (dest.first == to_x && dest.second == to_y) {
                    valid_dest = true;
                    break;
                }
            }

            if (valid_dest) {
                // لا ننفذ الحركة هنا! فقط نرجع المعلومات
                break;
            }
            else {
                cout << "Invalid destination! Must be adjacent and empty. Choose from available moves.\n";
            }
        }

        // إرجاع حركة تحتوي على الوجهة فقط
        // الـ update_board ستبحث عن القطعة المناسبة
        return new Move<char>(to_x, to_y, symbol);

    }
    else {
        // كمبيوتر عشوائي
        auto boardMatrix = player->get_board_ptr()->get_board_matrix();
        vector<pair<int, int>> player_tokens;
        vector<pair<pair<int, int>, pair<int, int>>> all_valid_moves;

        // جمع جميع القطع والحركات الممكنة
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (boardMatrix[i][j] == symbol) {
                    player_tokens.push_back({ i, j });

                    // تحقق من الحركات الممكنة من هذه القطعة
                    int directions[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
                    for (auto dir : directions) {
                        int nx = i + dir[0];
                        int ny = j + dir[1];
                        if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && boardMatrix[nx][ny] == ' ') {
                            all_valid_moves.push_back({ {i, j}, {nx, ny} });
                        }
                    }
                }
            }
        }

        if (!all_valid_moves.empty()) {
            auto move = all_valid_moves[rand() % all_valid_moves.size()];
            to_x = move.second.first;
            to_y = move.second.second;

            cout << player->get_name() << " moves to (" << to_x << "," << to_y << ")\n";
        }
        else {
            // حركة افتراضية إذا لم توجد حركات
            to_x = 1; to_y = 1;
        }

        return new Move<char>(to_x, to_y, symbol);
    }
}

Player<char>* FourByFourUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}