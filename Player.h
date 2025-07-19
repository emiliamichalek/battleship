#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
using namespace std;

class Player{
	public:
		Player(); // initializes both of player's boards to '.' characters
		void initialize_boards();  // start up the boards to display
		void display_boards(); // prints out computer's board and computer's opponent board
		void setPlayersOpponentBoard(int r, int c, char v); // changes the character at (r,c) on the player's opponent board to v
		char getPlayerBoardLocation(int r, int c);  // returns the value at (r,c) on the player's board
		void setPlayerBoardLocation(int r, int c, char v);  // changes the character at (r,c) on the player's board to v
		void setName(string n); // sets 'name' variable to contents of 'n'
		string getName(); // prints out contents of 'name' variable
		void tallyHit(int shipIndexNum); // increment the number of hits on the given ship and prints a statement if ship is sunk
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
		string name;
		const int NUM_SHIPS = 5;
};

Player::Player(){ // initializes both of player's boards to '.' characters

	for(int r=0; r<10; r++){
		for(int c=0; c<10; c++){
			board[r][c] = '.';
			opponent_board[r][c] = '.';
		}
	}

}

void Player::initialize_boards() { // start up the boards to display
	// Instructions:
	cout << "It's time to place your boats!" << endl;
	cout << "You first select if you want to place the boat horizontally (H) or vertically (V)." << endl;
	cout << "Then you select the location. The board is a 10 x 10 grid." << endl;
	cout << "The top left location of the board is (0, 0), and the bottom right location is (9, 9)." << endl;
	cout << "Depending on how you select your placement, you may not be able to place the boat in that position." << endl;
	cout << "If you place a boat vertically, it will start at the location you specify and go downward from there." << endl;
	cout << "If you place a boat horizontally, it will start at the location you specify and go rightward from there." << endl;
	cout << "Please choose carefully as you place your boats. Once you place a boat, it cannot be moved." << endl;
	cout << endl;
	// Instructions ^^^^^^^^^^^^^^^

	string shipName;
	char shipType;
	int length;
	bool badInput = false;
	for(int i=0; i<5; i++){
		switch(i){
		case 0:
			shipName = "Aircraft carrier";
			shipType = 'A';
			length = 5;
			break;
		case 1:
			shipName = "Battleship";
			shipType = 'B';
			length = 4;
			break;
		case 2:
			shipName = "Submarine";
			shipType = 'S';
			length = 3;
			break;
		case 3:
			shipName = "Destroyer";
			shipType = 'D';
			length = 3;
			break;
		case 4:
			shipName = "Patrol Boat";
			shipType = 'P';
			length = 2;
			break;
		default:
			break;
		}

		if(badInput){
			cout << "***Invalid input, please try again:\n" << endl;
			badInput = false;
		}else if(i !=0){
			cout << "Ship placed successfully.\n" << endl;
		}

		this->display_boards();
		cout << endl;

		// steps for ship placement
		cout << "Place your " << shipName << " (" << length << "). Type a direction vector and a starting location (row, column)."
				<< " Separate each character with spaces." << endl;
		cout << "For example: V 1 0 or H 4 5 \n : ";
		char orientation;
		cin >> orientation;
		//cout << "orientation: " << orientation << endl;
		int row;
		cin >> row;
		//cout << "row: " << row << endl;
		int col;
		cin >> col;
		//cout << "column: " << col << endl;

		cout << endl;

		bool interference = false;
		// checks if ship can be placed in player's selected location ********************************
		if(orientation == 'V'){ // orientation : vertical
			for(int i=0; i<length; i++){ // goes down from starting point
				if((board[row+i][col] != '.') || ((row+i) > 9)){
					interference = true;
				}
			}
		}else if(orientation == 'H'){ // orientation : horizontal
			for(int i=0; i<length; i++){ // goes right from starting point
				if((board[row][col+i] != '.') || ((col+i) > 9)){
					interference = true;
				}
			}
		}else{
			interference = true;
		}

		// put in the ship if there's no interference ************************************************
		if(interference){
			badInput = true;
			i -= 1;
		}else{
			if(orientation == 'V'){ // orientation : vertical
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

	}

	cout << "All Ships successfully placed." << endl;
	/*
	cout << "Ships vector: " << endl;
	for(int i=0; i < ships.size(); i++){
		std::cout << ships.at(i) << ' ';
	}
	cout << endl;
	*/

}

void Player::display_boards(){ // prints out computer's board and computer's opponent board
	if(ships.size() >= 5){
		cout << "\n--------------------------------------------------------------------------------------------" << endl;
	}

	cout << "Player's Board\n" << "*************" << endl;
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
	printf("%-3s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s%-2s\n", "  ", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_");
	for(int i = 0; i < 10; i++){
		cout << to_string(i) << " |";
		for(int j = 0; j < 10; j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	if(ships.size() >= 5){
		cout << "Player's Opponent Board\n" << "*************" << endl;
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
}

void Player::setPlayersOpponentBoard(int r, int c, char v){ // changes the character at (r,c) on the player's opponent board to v
	opponent_board[r][c] = v;
}

char Player::getPlayerBoardLocation(int r, int c){ // returns the value at (r,c) on the player's board
	return board[r][c];
}

void Player::setPlayerBoardLocation(int r, int c, char v){ // changes the character at (r,c) on the player's board to v
	board[r][c] = v;
}

void Player::setName(string n){ // sets 'name' variable to contents of 'n'
	name = n;
}

string Player::getName(){ // prints out contents of 'name' variable
	return name;
}

void Player::tallyHit(int shipIndexNum){ // increment the number of hits on the given ship and prints a statement if ship is sunk
	ships.at(shipIndexNum) -= 1;
	if(ships.at(shipIndexNum) == 0){
		switch(shipIndexNum){
		case 0:
			cout << "Player's Aircraft Carrier is sunk!" << endl;
			break;
		case 1:
			cout << "Player's Battleship is sunk!" << endl;
			break;
		case 2:
			cout << "Player's Submarine is sunk!" << endl;
			break;
		case 3:
			cout << "Player's Destroyer is sunk!" << endl;
			break;
		case 4:
			cout << "Player's Patrol Boat is sunk!" << endl;
			break;
		default:
			break;
		}
	}
}

bool Player::check_status(){ // see if all the Computers' ships are sunk!
	bool continueGame = false;
	for(auto n:ships){
		if(n != 0){
			continueGame = true;
		}
	}
	return continueGame;
}

#endif























