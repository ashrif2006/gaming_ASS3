#include "FourByFourTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

FourByFourBoard::FourByFourBoard() : Board<char>(4, 4), current_player_symbol('X') {
    // تهيئة اللوحة الفارغة
    board = {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    };
    
    // إضافة القطع الأولية
    pieces.push_back(Piece(0, 1, 'X')); // X في (0,1)
    pieces.push_back(Piece(0, 3, 'X')); // X في (0,3)
    pieces.push_back(Piece(3, 0, 'X')); // X في (3,0)
    pieces.push_back(Piece(3, 2, 'X')); // X في (3,2)
    
    pieces.push_back(Piece(0, 0, 'O')); // O في (0,0)
    pieces.push_back(Piece(0, 2, 'O')); // O في (0,2)
    pieces.push_back(Piece(3, 1, 'O')); // O في (3,1)
    pieces.push_back(Piece(3, 3, 'O')); // O في (3,3)
    
    // تحديث اللوحة بالقطع
    for (const auto& piece : pieces) {
        board[piece.x][piece.y] = piece.symbol;
    }
    
    n_moves = 0;
}

int FourByFourBoard::find_piece_index(int x, int y) {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i].x == x && pieces[i].y == y) {
            return i;
        }
    }
    return -1; // لم يتم العثور على قطعة
}

bool FourByFourBoard::is_valid_move(int from_x, int from_y, int to_x, int to_y, char symbol) {
    // التحقق من أن الإحداثيات ضمن النطاق
    if (from_x < 0 || from_x > 3 || from_y < 0 || from_y > 3 ||
        to_x < 0 || to_x > 3 || to_y < 0 || to_y > 3) {
        return false;
    }
    
    // التحقق من أن الخلية الهدف فارغة
    if (board[to_x][to_y] != ' ') {
        return false;
    }
    
    // التحقق من أن القطعة في الخلية المصدر تعود للاعب الحالي
    if (board[from_x][from_y] != symbol) {
        return false;
    }
    
    // التحقق من أن الحركة إلى خانة مجاورة (ليست قطرية)
    int dx = abs(to_x - from_x);
    int dy = abs(to_y - from_y);
    
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1); // أفقي أو عمودي فقط
}

bool FourByFourBoard::move_piece(int from_x, int from_y, int to_x, int to_y, char symbol) {
    if (!is_valid_move(from_x, from_y, to_x, to_y, symbol)) {
        return false;
    }
    
    // العثور على القطعة وتحريكها
    int piece_index = find_piece_index(from_x, from_y);
    if (piece_index == -1) {
        return false;
    }
    
    // تحديث اللوحة
    board[from_x][from_y] = ' ';
    board[to_x][to_y] = symbol;
    
    // تحديث موقع القطعة
    pieces[piece_index].x = to_x;
    pieces[piece_index].y = to_y;
    
    n_moves++;
    current_player_symbol = (current_player_symbol == 'X') ? 'O' : 'X';
    return true;
}

bool FourByFourBoard::update_board(Move<char>* move) {
    // في هذه اللعبة، Move يجب أن يحتوي على معلومات "من" و "إلى"
    // للتبسيط، سنستخدم move->get_x() للإحداثيات الهدف
    // وسنطلب من اللاعب اختيار القطعة في الـ UI
    
    // هذا تنفيذ مبسط - سنعالج الحركة في الـ UI
    return true;
}

bool FourByFourBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    
    // التحقق من الصفوف - 3 متتالية
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol)
                return true;
        }
    }
    
    // التحقق من الأعمدة - 3 متتالية
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 2; ++i) {
            if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol)
                return true;
        }
    }
    
    // التحقق من الأقطار
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            // قطر رئيسي
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol)
                return true;
        }
    }
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 2; j < 4; ++j) {
            // قطر ثانوي
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol)
                return true;
        }
    }
    
    return false;
}

bool FourByFourBoard::is_lose(Player<char>* player) {
    return false;
}

bool FourByFourBoard::is_draw(Player<char>* player) {
    // التعادل بعد عدد كبير من الحركات بدون فائز
    return n_moves > 30 && !is_win(player);
}

bool FourByFourBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// تنفيذ الـ UI
FourByFourUI::FourByFourUI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 3) {}

Move<char>* FourByFourUI::get_complex_move(Player<char>* player) {
    char symbol = player->get_symbol();
    auto board_ptr = dynamic_cast<FourByFourBoard*>(player->get_board_ptr());
    
    if (player->get_type() == PlayerType::HUMAN) {
        int from_x, from_y, to_x, to_y;
        
        while (true) {
            cout << player->get_name() << "'s turn (symbol: " << symbol << ")\n";
            
            // عرض القطع المتاحة للتحريك
            cout << "Your pieces are at: ";
            auto boardMatrix = player->get_board_ptr()->get_board_matrix();
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (boardMatrix[i][j] == symbol) {
                        cout << "(" << i << "," << j << ") ";
                    }
                }
            }
            cout << endl;
            
            // الحصول على القطعة المراد تحريكها
            cout << "Enter piece to move (row column): ";
            cin >> from_x >> from_y;
            
            // الحصول على الوجهة
            cout << "Enter destination (row column): ";
            cin >> to_x >> to_y;
            
            if (board_ptr->move_piece(from_x, from_y, to_x, to_y, symbol)) {
                break;
            } else {
                cout << "Invalid move! Try again.\n";
            }
        }
        
        // إرجاع حركة وهمية (لأن الحركة تمت بالفعل في move_piece)
        return new Move<char>(to_x, to_y, symbol);
        
    } else {
        // كمبيوتر عشوائي
        auto boardMatrix = player->get_board_ptr()->get_board_matrix();
        vector<pair<int, int>> player_pieces;
        vector<pair<int, int>> empty_cells;
        
        // جمع قطع الكمبيوتر والخلايا الفارغة
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (boardMatrix[i][j] == symbol) {
                    player_pieces.push_back({i, j});
                } else if (boardMatrix[i][j] == ' ') {
                    empty_cells.push_back({i, j});
                }
            }
        }
        
        // محاولة إيجاد حركة قانونية
        for (int attempt = 0; attempt < 100; attempt++) {
            auto from = player_pieces[rand() % player_pieces.size()];
            auto to = empty_cells[rand() % empty_cells.size()];
            
            if (board_ptr->move_piece(from.first, from.second, to.first, to.second, symbol)) {
                cout << player->get_name() << " moved from (" << from.first << "," << from.second 
                     << ") to (" << to.first << "," << to.second << ")\n";
                return new Move<char>(to.first, to.second, symbol);
            }
        }
        
        // إذا فشلت جميع المحاولات، ارجع حركة عشوائية
        return new Move<char>(0, 0, symbol);
    }
}

Move<char>* FourByFourUI::get_move(Player<char>* player) {
    return get_complex_move(player);
}

Player<char>* FourByFourUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}