
#include "sus.h"
#include <cctype>
SusBoard::SusBoard() : Board<char>(3,3) {
	for(int i=0;i<rows;i++)
		for(int j=0;j<columns;j++)
			board[i][j] = ' ';
}

bool SusBoard::update_board(Move<char>* move) {
	int r = move->get_x();
	int c = move->get_y();
	char sym = move->get_symbol();
	sym = toupper(sym);

	int player_idx = current_player;

	if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ')
		return false;

	if (sym != 'S' && sym != 'U') {
		std::cout << "Invalid symbol. Please use S or U.\n";
		return false;
	}

	board[r][c] = sym;
	int score_count = 0;

	// التحقق الأفقي

	if (c == 2 && board[r][c - 1] == 'U' && board[r][c - 2] == 'S') score_count++;

	if (c == 0 && board[r][c + 1] == 'U' && board[r][c + 2] == 'S') score_count++;

	if (sym == 'U' && c == 1 && board[r][c - 1] == 'S' && board[r][c + 1] == 'S') score_count++;

	// التحقق العمودي

	if (r == 2 && board[r - 1][c] == 'U' && board[r - 2][c] == 'S') score_count++;

	if (r == 0 && board[r + 1][c] == 'U' && board[r + 2][c] == 'S') score_count++;

	if (sym == 'U' && r == 1 && board[r - 1][c] == 'S' && board[r + 1][c] == 'S') score_count++;

	// التحقق القطري (الرئيسي)

	if (r == 2 && c == 2 && board[r - 1][c - 1] == 'U' && board[r - 2][c - 2] == 'S') score_count++;

	if (r == 0 && c == 0 && board[r + 1][c + 1] == 'U' && board[r + 2][c + 2] == 'S') score_count++;

	if (sym == 'U' && r == 1 && c == 1 && board[r - 1][c - 1] == 'S' && board[r + 1][c + 1] == 'S') score_count++;

	// التحقق القطري (العكسي)

	if (r == 2 && c == 0 && board[r - 1][c + 1] == 'U' && board[r - 2][c + 2] == 'S') score_count++;

	if (r == 0 && c == 2 && board[r + 1][c - 1] == 'U' && board[r + 2][c - 2] == 'S') score_count++;

	if (sym == 'U' && r == 1 && c == 1 && board[r - 1][c + 1] == 'S' && board[r + 1][c - 1] == 'S') score_count++;

	player_scores[player_idx] += score_count;
	n_moves++;
	current_player = 1 - current_player;
	return true;

}
/*المشكله هنا ان اللاعب بيخسر او بيفوز مش لما يعمل حاجه معينه هنا بيكسب او بيفوز لما البورد تتملي عشان كده حطيت الشرط ده */
bool SusBoard::is_win(Player<char>* player) {
	if (!game_is_over(player)) {
		return false;
	}
	int idx = (player->get_symbol() == 'S') ? 0 : 1;
	int other = 1 - idx;
	return player_scores[idx] > player_scores[other];
}

bool SusBoard::is_lose(Player<char>* player) {
	if (!game_is_over(player)) {
		return false;
	}
	
	int idx = (player->get_symbol() == 'S') ? 0 : 1;
	int other = 1 - idx;
	return player_scores[idx] < player_scores[other];
}
bool SusBoard::is_draw(Player<char>* player) {
	return player_scores[0] == player_scores[1] && game_is_over(player);
}
bool SusBoard::game_is_over(Player<char>* player) {
	return n_moves >= 9;
}
int SusBoard::get_player_score(int index) const {
	return player_scores[index];
}
SusUI::SusUI(int cell_width) : UI<char>("S-U-S Game", 3) {}

Move<char>* SusUI::get_move(Player<char>* player) {

	int r, c;
	char sym;

	if (player->get_type() == PlayerType::COMPUTER) {
	
		srand(time(0));
		r = rand() % 3;
		c = rand() % 3;
		sym = (rand() % 2 == 0) ? 'S' : 'U';


	}
	else { 
		cout << player->get_name() << " move (row col symbol): ";
		cin >> r >> c >> sym;
	}

	return new Move<char>(r, c, sym);
}


Player<char>* SusUI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name,symbol,type);
}
Player<char>** SusUI::setup_players() {
	Player<char>** players = new Player<char>*[2];
	string name1, name2;
	int choice;

	cout << "Enter Player 1 name: ";
	getline(cin >> std::ws, name1);
	cout << "\nSelect Player 2 type:\n";
	cout << "1. Human\n";
	cout << "2. Computer (AI)\n";
	cout << "Enter choice (1 or 2): ";
	cin >> choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	players[0] = create_player(name1, 'S', PlayerType::HUMAN);

	if (choice == 2) {
		name2 = "Computer (AI)";
		players[1] = create_player(name2, 'U', PlayerType::COMPUTER);     
	}
	else {
		cout << "Enter Player 2 name: ";
		getline(cin >> std::ws, name2);
		players[1] = create_player(name2, 'U', PlayerType::HUMAN);
	}

	return players;
}


void SusUI::display_final_results(Board<char>* board, Player<char>** players) {
	SusBoard* sus_board = dynamic_cast<SusBoard*>(board);
	if(!board->game_is_over(players[0])) {
		cout << "The game is not over yet.\n";
		return;
	}
	if(board->is_draw(players[0])) {
		cout << "The game is a draw!\n";
	}
	
	string winner_name;
	string loser_name;
	if(board->is_win(players[0])) {
		winner_name = players[0]->get_name();
		loser_name = players[1]->get_name();
	} else {
		winner_name = players[1]->get_name();
		loser_name = players[0]->get_name();
	}
	cout << "Winner: " << winner_name << " with score " << sus_board->get_player_score((winner_name == players[0]->get_name()) ? 0 : 1) << "\n";
	cout << "Loser: " << loser_name << " with score " << sus_board->get_player_score((loser_name == players[0]->get_name()) ? 0 : 1) << "\n";

}