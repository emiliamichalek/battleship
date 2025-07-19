
// Emilia Michalek : Battleship
// 12/9/2022

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Battleship.h"
using namespace std;


int main(){
	bool winner = false;
	int row, col;
	
	cout << "\nWelcome to the game of BATTLESHIP!\n"
			<< "The objective of this game is to sink all of your opponent's boats.\n"
			<< "Each player has five (5) boats. Each boat has a name and a size.\n"
			<< "Here are the boat names and sizes:\n"
			<< "Aircraft Carrier 5\n"
			<< "BATTLESHIP 4\n"
			<< "Submarine 3\n"
			<< "Destroyer 3\n"
			<< "Patrol Boat 2\n" << endl;
	Battleship game;
	
	srand(time(NULL));
	int turn = rand() % 2;  //1 is player turn, and 2 is comp turn
	
	while(!winner){
		if(turn == 1){   //Player goes first.
			cout << "Please enter your guess (Row Column): ";
			cin >> row >> col;
			game.check_player_guess(row, col);
			if(!game.get_status()){
				//Player wins.
				cout << "Player wins!\n";
				winner = true;
				break;
			}
			game.check_computer_guess();
			if(!game.get_status()){
				cout << "Computer wins!\n";
				winner = true;
				break;
			}
		}else{    //Computer goes first.
			game.check_computer_guess();
			if(!game.get_status()){
				cout << "Computer wins!\n";
				winner = true;
				break;
			}
			cout << "Please enter your guess (Row Column): ";
			cin >> row >> col;
			game.check_player_guess(row, col);
			if(!game.get_status()){
				cout << "Player wins!\n";
				winner = true;
				break;
			}
		}
	}
	return 0;
}


/* Two player game.
   if(!game.get_status()){
		//Player wins.
		break;
   }
   else{
		cout << "Are you done with your move?";
		//Get yes or no here and then go to a blank screen and prompt for the next player
		//to begin their turn. This way, neither player sees the other players' board.
   }
   */

