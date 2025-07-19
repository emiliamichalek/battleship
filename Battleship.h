#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <iostream>
#include <ctime>
#include <random>
#include "Computer.h"
#include "Player.h"
using namespace std;

class Battleship{
	public:
		Battleship(); // initializes all variables, gets players name, and initializes/displays boards
		void check_player_guess(int row, int col); // checks player's guess on computer's board
		void check_computer_guess(); // checks computer's guess on player's board
		bool get_status(); // checks if anyone won
	private:
		Player player;
		Computer computer;
		bool status;  //if true => game on!, else if false => someone won!
		int compVisible; // 1 = only player boards
						 // 2 = both player and computer boards
};


Battleship::Battleship(){ // initializes all variables, gets players name, and initializes/displays boards
	string n;
	compVisible = 0; // to avoid warning
	cout << "Enter 1 if you want to play regular battleship and 2 if you want to play with"
			<< " computer boards visible:" << endl;
	cin >> compVisible;

	cout << "Player, please enter your name: ";
	cin >> n;
	player.setName(n);
	player.initialize_boards();
	computer.initialize_boards();
	cout << "Boards and Ships initialized!" << endl;

	player.display_boards();
	if(compVisible == 2){
		computer.display_boards();
	}

	cout << endl;
	cout << "***START OF GAME***" << endl;

	status = true;

}

void Battleship::check_player_guess(int row, int col){  // checks player's guess on computer's board
	while(row > 9 || col > 9 || row < 0 || col < 0){
		cout << "Please enter a valid row and column: " << endl;
		cin >> row;
		cin >> col;
	}
	char guessVal = computer.getCompBoardLocation(row, col);
	if(guessVal == '.'){
		cout << "Miss by " << player.getName() << "!" << endl;
		computer.setCompBoardLocation(row, col, 'M');
		player.setPlayersOpponentBoard(row, col, 'M');
	}else if(guessVal != 'X'){
		cout << "Hit by " << player.getName() << "!" << endl;
		computer.setCompBoardLocation(row, col, 'X');
		player.setPlayersOpponentBoard(row, col, 'X');
		switch(guessVal){
		case 'A':
			// Aircraft Carrier
			computer.tallyHit(0);
			break;
		case 'B':
			// Battleship
			computer.tallyHit(1);
			break;
		case 'S':
			// Submarine
			computer.tallyHit(2);
			break;
		case 'D':
			// Destroyer
			computer.tallyHit(3);
			break;
		case 'P':
			// Patrol Boat
			computer.tallyHit(4);
			break;
		default:
			break;
		}
	}else if(guessVal == 'X'){
		cout << "This location was already hit" << endl;
	}

	player.display_boards();
}

void Battleship::check_computer_guess(){ // checks computer's guess on player's board
	srand(time(NULL));
	int row = rand() % 10; // chooses random row
	int col = rand() % 10; // chooses random column
	char guessVal = player.getPlayerBoardLocation(row, col);

	if(guessVal == '.'){
		// computer miss
		cout << "Miss by computer! At (" << row << "," << col << ")" << endl;
		player.setPlayerBoardLocation(row, col, 'M');
		computer.setCompsOpponentBoard(row, col, 'M');
	}else if(guessVal != 'X' && guessVal != 'M'){
		cout << "Hit by computer! At (" << row << "," << col << ")" << endl;
		player.setPlayerBoardLocation(row, col, 'X');
		computer.setCompsOpponentBoard(row, col, 'X');
		switch(guessVal){
		case 'A':
			// Aircraft Carrier
			player.tallyHit(0);
			break;
		case 'B':
			// Battleship
			player.tallyHit(1);
			break;
		case 'S':
			// Submarine
			player.tallyHit(2);
			break;
		case 'D':
			// Destroyer
			player.tallyHit(3);
			break;
		case 'P':
			// Patrol Boat
			player.tallyHit(4);
			break;
		default:
			break;
		}
	}

	if(compVisible == 2){
		computer.display_boards();
	}

}

bool Battleship::get_status(){ // checks if anyone won
	if(computer.check_status() && player.check_status()){
		status = true;
	}else{
		status = false;
	}
	return status;
}






#endif
