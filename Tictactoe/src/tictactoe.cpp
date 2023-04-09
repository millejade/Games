#include "../include/tictactoe.h"
#include <iostream>
#include <vector>
#include <string>


void Player::create_new_player(std::string name){
	players.push_back(name);
	std::cout << "Player" << " '" << name << "' " << "created." << std::endl;
	selected_player = name;
}

void Player::select_player(){
	std::cout << "List of players:" << std::endl;
	for(std::string name : players){
		std::cout << "-\t" << name << std::endl;
	}
	std::string name;
	bool check_player = true;

	while(check_player){
		std::cout << "Enter your name:\t";
		std::cin >> name;

		for(std::string n : Player::players){
			if(name == n){
				std::cout << "Playing as " << name << "." << std::endl;
				selected_player = name;
				check_player = false;
				break;
			}
		}
		if(check_player) std::cout << "Player not found!" << std::endl;
	}
}

bool Player::disp_player_selection(){
	char select = ' ';
	do{
		std::cout << "X: " << "Create new player" << std::endl;
		std::cout << "O: " << "Select player" << std::endl;
		std::cin >> select;
	}while(select != 'O' && select != 'X');

	if(select == 'O') return false;
	else return true;
}


void Game_Menu::init_menu(){
	char btn;
	std::cout << "Player: " << p.selected_player << std::endl;
	do{
		std::cout << "Input: " << std::endl;
		std::cout << "G" << " : " << "Start the game" << std::endl;
		std::cout << "S" << " : " << "Select player" << std::endl;
		std::cout << "Q" << " : " << "Quit the game" << std::endl;
		std::cin >> btn;
	}while((btn != 'G') && (btn != 'S') && (btn != 'Q'));

	switch(btn){
		case 'G': // Game start
			game_option[0] = true;
			break;

		case 'S': // Selection of player
			game_option[1] = true;
			break;

		case 'Q': // Quit game
			game_option[2] = true;
			break;

		default:
			std::cout << "[WARNING]: Invalid option! Select option again.";
	}
}

void Game_Menu::playing(){
	std::cout << "Hello " << p.selected_player << "!" << std::endl;
	ttt.init_board();
	std::cout << "=============" << std::endl;
	do{
		ttt.player_move();
		ttt.update_board();
		std::cout << "=============" << std::endl;

		winner = ttt.check_winner();
		if(winner == 'X'){
			std::cout << "YOU WIN!" << std::endl;
			break;
		}else if(winner == 'O'){
			std::cout << "YOU LOSE!" << std::endl;
			break;
		}

		if(ttt.check_draw()){
			std::cout << "DRAW!" << std::endl;
			break;
		}

		ttt.ai_move();
		ttt.update_board();
		std::cout << "=============" << std::endl;

		winner = ttt.check_winner();
		if(winner == 'X'){
			std::cout << "YOU WIN!" << std::endl;
			break;
		}else if(winner == 'O'){
			std::cout << "YOU LOSE!" << std::endl;
			break;
		}

		if(ttt.check_draw()){
			std::cout << "DRAW!" << std::endl;
			break;
		}


	} while(true);

	std::cout << "Game Ends!" << std::endl;
}

void Game_Menu::player_selection(){
	if(p.disp_player_selection()){
		std::string name;
		std::cout << "Enter your name:\t";
		std::cin >> name;
		p.create_new_player(name);
	}else{
		p.select_player();
	}
}

void Game_Menu::quitting(){
}

void Game_Menu::start_process(){
	if(game_option[0]){
		playing();
		// increment the win/lose/draw of the player
		// show stat of the player
		// go back to main menu
		game_option[0] = false;
	}else if(game_option[1]){
		player_selection();
		game_option[1] = false;
	}else if(game_option[2]){
		quitting();
		game_option[2] = false;
	}
}


void Tictactoe::init_board(){
	char* p;
	for(p = *board; p <= (*(board + 2)+2); p++){  // assigned an empty character in a 3x3 array
		*p = ' ';
	}

	std::cout << "| " << Tictactoe::board[0][0] << " | " << Tictactoe::board[0][1] << " | " << Tictactoe::board[0][2] << " |" << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "| " << Tictactoe::board[1][0] << " | " << Tictactoe::board[1][1] << " | " << Tictactoe::board[1][2] << " |" << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "| " << Tictactoe::board[2][0] << " | " << Tictactoe::board[2][1] << " | " << Tictactoe::board[2][2] << " |" << std::endl;
}

void Tictactoe::update_board(){
	std::cout << "| " << Tictactoe::board[0][0] << " | " << Tictactoe::board[0][1] << " | " << Tictactoe::board[0][2] << " |" << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "| " << Tictactoe::board[1][0] << " | " << Tictactoe::board[1][1] << " | " << Tictactoe::board[1][2] << " |" << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "| " << Tictactoe::board[2][0] << " | " << Tictactoe::board[2][1] << " | " << Tictactoe::board[2][2] << " |" << std::endl;
}

void Tictactoe::check_pieces(){ // for debugging only
	char* p;
	int i = 1;
	for(p = *board; p <= (*(board + 2)+2); p++){  // assigned an empty character in a 3x3 array
		std::cout << i << " : "<< *p << std::endl;
		i++;
	}
}

void Tictactoe::player_move(){
	int row, colm;
	do{
		std::cout << "Make your move\nRow [1 2 3]\tColumn [1 2 3]" << std::endl;
		std::cout << "ROW: ";
		std::cin >> row;
		std::cout << "COL: ";
		std::cin >> colm;

		if((row > 0 && row < 4) && (colm > 0 && colm < 4)){ // valid rows and column only

			if(Tictactoe::board[row-1][colm-1] == ' '){
				Tictactoe::board[row-1][colm-1] = 'X';
				break;
			}else{
				std::cout << "[WARNING]: Position already used! Please select other position." << std::endl;
			}

		}else{

			std::cout << "[WARNING]: Invalid position. Please select other position." << std::endl; 

		}
	}while(true);
}

void Tictactoe::ai_move(){
	int row, colm, flag = 1;
	do{
		row = (rand() % 3) + 1;
		colm = (rand() % 3) + 1;

		if(Tictactoe::board[row-1][colm-1] == ' '){
			Tictactoe::board[row-1][colm-1] = 'O';
			flag = 0;
		}
	}while(flag);
}

bool Tictactoe::check_draw(){
	char* p;
	int count = 0;
	for(p = *board; p <= (*(board + 2)+2); p++){  // assigned an empty character in a 3x3 array
		if(*p != ' ') count++;
	}
	if(count == 9) return true;
	else return false;
}

char Tictactoe::check_winner(){
	/*
	HORIZONTAL
	00 - 01 - 02
	10 - 11 - 12
	20 - 21 - 22

	VERTICAL
	00 - 10 - 20
	01 - 11 - 21
	02 - 12 - 22

	SLANT
	(1,1) - (2,2) - (3,3)
	(3,1) - (2,2) - (1,3)

	*/

	int player1 = 0;
	int ai = 0;

	/*------------ HORIZONTAL -----------*/
	char* p;
		// Row 1
	for(p=*board; p<=*board+2; p++){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

		// Row 2
	for(p=*(board+1); p<=(*(board+1))+2; p++){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

		// Row 3
	for(p=*(board+2); p<=(*(board+2))+2; p++){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;


	/*------------ VERTICAL ------------*/
		// Column 1
	for(p=*(board); p<=*(board+2); p += 3){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

		// Column 2
	for(p=(*board)+1; p<=(*(board+2))+1; p += 3){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

		// Column 3
	for(p=(*board)+2; p<=(*(board+2))+2; p += 3){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

	/*--------------- SLANT ----------------*/
	for(p=*board; p<=(*(board+2))+2; p += 4){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;

	for(p=*board + 2; p<=*(board+2); p += 2){
		if(*p == 'X')
			player1++;
		else if(*p == 'O')
			ai++;
	}
	if(player1==3)
		return 'X';
	else if(ai==3)
		return 'O';
	player1 = 0;
	ai = 0;
}