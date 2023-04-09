#include <iostream>
#include "../include/tictactoe.h"

int main(){
	Game_Menu gm;
	while(1){
		gm.init_menu();
		if(gm.game_option[2]) break; // quit game
		gm.start_process();
	}
	return 0;
}
