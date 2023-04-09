#pragma once
#include <vector>
#include <string>
#include <map>

class Player{

public:
	std::vector <std::string> players{"Darna", "Cardo", "Dwayne"};
	// std::map <std::string, int> players{
	// 	{"Darna", 0},
	// 	{"Cardo", 0},
	// 	{"Dwayne", 0}
	// }
	std::string selected_player = players.front();
	void create_new_player(std::string name);
	void select_player();
	bool disp_player_selection();
private:

};

class Tictactoe{

private:
	char board[3][3];

public:
	void init_board();
	void update_board();
	void check_pieces();
	void player_move();
	void ai_move();
	char check_winner();
	bool check_draw();
	// char show_winner();


};

class Game_Menu{
public:
	// void show_menu();
	Player p;
	Tictactoe ttt;
	char winner = ' ';
	bool game_option[3] = {false, false, false};
	void init_menu();
	void playing();
	void player_selection();
	void quitting();
	void start_process();


};
