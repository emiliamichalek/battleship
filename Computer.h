#ifndef COMPUTER_H
#define COMPUTER_H
#include <vector>
#include <string>
#include <ctime>
#include <random>
using namespace std;

class Computer{
	public:
		Computer(); // initializes both of computer's boards to '.' characters
		void initialize_boards();  // start up the boards to display
		void display_boards(); // prints out computer's board and computer's opponent board
		void setCompsOpponentBoard(int r, int c, char v); // changes the character at (r,c) on the computer's opponent board to v
		char getCompBoardLocation(int r, int c);  // returns the value at (r,c) on the computer's board
		void setCompBoardLocation(int r, int c, char v);  // changes the character at (r,c) on the computer's board to v
		void tallyHit(int shipIndexNum);   //increment the number of hits on the given ship and prints a statement if ship is sunk
		bool check_status(); // see if all the Computers' ships are sunk!
	private:
		vector<int> ships;
		/* Index 0: Aircraft Carrier (5)
		 * Index 1: Battleship (4)
		 * Index 2: Submarine (3)
		 * Index 3: Destroyer (3)
		 * Index 4: Patrol Boat (2)
		 */
		char board[10][10];
		char opponent_board[10][10];
		const int NUM_SHIPS = 5;
};

Computer::Computer(){ // initializes both of computer's boards to '.' characters

	for(int r=0; r<10; r++){
		for(int c=0; c<10; c++){
			board[r][c] = '.';
			opponent_board[r][c] = '.';
		}
	}

}

void Computer::initialize_boards(){  // start up the boards to display
	srand(time(NULL));
	for(int i=0; i<5; i++){

		char shipType;
		int length;
		switch(i){
		case 0:
			shipType = 'A';
			length = 5;
			break;
		case 1:
			shipType = 'B';
			length = 4;
			break;
		case 2:
			shipType = 'S';
			length = 3;
			break;
		case 3:
			shipType = 'D';
			length = 3;
			break;
		case 4:
			shipType = 'P';
			length = 2;
			break;
		default:
			break;
		}

		// Find random location for ship *************************************************************

		//cout << "ship: " << shipType << endl;

		int orientation = rand() % 2;  //1 is vertical, and 0 is horizontal
		//cout << "Orientation: " << orientation << endl;

		int row = rand() % 10; // random starting row
		//cout << "Starting Row: " << row << endl;

		int col = rand() % 10; // random starting column
		//cout << "Starting Col: " << col << endl;


		bool interference = false;
		// checks if ship can be placed in randomly selected location ********************************
		if(orientation == 1){ // orientation : vertical
			for(int i=0; i<length; i++){ // goes down from starting point
				if((board[row+i][col] != '.') || ((row+i) > 9)){
					interference = true;
				}
			}
		}else{ // orientation : horizontal
			for(int i=0; i<length; i++){ // goes right from starting point
				if((board[row][col+i] != '.') || ((col+i) > 9)){
					interference = true;
				}
			}
		}

		// put in the ship if there's no interference ************************************************
		if(interference){
			i -= 1;
		}else{
			if(orientation == 1){ // orientation : vertical
				for(int i=0; i<length; i++){
					board[row+i][col] = shipType;
				}
			}else{ // orientation : horizontal
				for(int i=0; i<length; i++){
					board[row][col+i] = shipType;
				}
			}
			ships.push_back(length);
		}

		// test:
		/*
		cout << "Ships vector: " << endl;
		for(int i=0; i < ships.size(); i++){
			std::cout << ships.at(i) << ' ';
		}
		cout << endl;
		*/

	}

}

void Computer::display_boards(){ // prints out computer's board and computer's opponent board
	cout << "\n--------------------------------------------------------------------------------------------" << endl;
	cout << "Computer's Board\n" << "*************" << endl;
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_");
	for(int i = 0; i < 10; i++){
		cout << to_string(i) << " |";
		for(int j = 0; j < 10; j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Computer's Opponent Board\n" << "*************" << endl;
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_");
	for(int i = 0; i < 10; i++){
		cout << to_string(i) << " |";
		for(int j = 0; j < 10; j++){
			cout << opponent_board[i][j] << " ";
		}
		cout << endl;
	}
}

void Computer::setCompsOpponentBoard(int r, int c, char v){ // changes the character at (r,c) on the computer's opponent board to v
	opponent_board[r][c] = v;
}

char Computer::getCompBoardLocation(int r, int c){ // returns the value at (r,c) on the computer's board
	return board[r][c];
}

void Computer::setCompBoardLocation(int r, int c, char v){ // changes the character at (r,c) on the computer's board to v
	board[r][c] = v;
}

void Computer::tallyHit(int shipIndexNum){ //increment the number of hits on the given ship and prints a statement if ship is sunk
	ships.at(shipIndexNum) -= 1;
	if(ships.at(shipIndexNum) == 0){
		switch(shipIndexNum){
		case 0:
			cout << "Computer's Aircraft Carrier is sunk!" << endl;
			break;
		case 1:
			cout << "Computer's Battleship is sunk!" << endl;
			break;
		case 2:
			cout << "Computer's Submarine is sunk!" << endl;
			break;
		case 3:
			cout << "Computer's Destroyer is sunk!" << endl;
			break;
		case 4:
			cout << "Computer's Patrol Boat is sunk!" << endl;
			break;
		default:
			break;
		}
	}
}

bool Computer::check_status(){ // see if all the Computers' ships are sunk!
	bool continueGame = false;
	for(auto n:ships){
		if(n != 0){
			continueGame = true;
		}
	}
	return continueGame;
}




#endif
