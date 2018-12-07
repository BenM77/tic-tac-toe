////////////////////////////////////
// Algorithms: Exam 2
// Tic-Tac-Toe
// Tristan Hildahl and Ben Michael
////////////////////////////////////
// Sources
// https://www.wikihow.com/Win-at-Tic-Tac-Toe
// Used as a baseline for logic behind how to win/never lose Tic-Tac-Toe depending on the situation
//
// https://stackoverflow.com/questions/9773607/optimal-algorithm-for-seeing-who-won-a-tick-tac-toe-game
// Answer by Ali Ferhat helped us to conceptualize the best way to see if someone has won the game
////////////////////////////////////

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

bool playerTurn(int *board, int *boardWins);
bool cpuTurn(int *board, int *boardWins, int turnCount);
void printScreen(int *board);
bool checkWin(int *boardWins);
void adjustBoardWins(int *boardWins, int user, int location);
int findWin(int *board, int winCondition);


int main() {
	srand(time(NULL));

	//The 9 squares on the board default to empty: -1 is an O, 1 is an X
	int boardFill[9] = { 0,0,0,0,0,0,0,0,0 };
	int *board = boardFill;
	int boardWins[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	//First 8 values: Player amount, last 8: enemy amount towards winning at each condition
	int *winConditions = boardWins;


	string firstPlayer;
	bool playersTurn = 0;

	cout << "Let's play Tic-Tac-Toe!" << endl;

	bool invalidInput =  true;

	while (invalidInput) {
		cout << "Would you like to go 1st or 2nd? (Enter '1' or '2')" << endl;
		cin >> firstPlayer;
		if (firstPlayer != "1" && firstPlayer != "2") {
			invalidInput = true;
			cout << "Invalid Input. Try again." << endl;
		}
		else
			invalidInput = false;
	}

	printScreen(board);

	if (firstPlayer == "1")
		playersTurn = 1;

	bool playerWon = 0;
	bool cpuWon = 0;
	int turnCount = 0;

	while (!playerWon && !cpuWon && turnCount < 9) {

		if (playersTurn)
			playerWon = playerTurn(board, boardWins);
		else
			cpuWon = cpuTurn(board, boardWins, turnCount);

		playersTurn = !playersTurn;
		turnCount++;
	}

	if (playerWon)
		cout << "Congratulations! You Win!\nWait, that shouldn't have happened..." << endl;
	else if (cpuWon)
		cout << "Too bad, you Lose!";
	else
		cout << "Draw!";

	int wait;
	cin >> wait;

	return 0;
}

bool playerTurn(int *board, int *boardWins) {
	string input;

	cout << "You are X's. Where would you like to go? (Enter in a number from 1 to 9 representing the position) " << endl;

	bool invalidInput = true;

	while (invalidInput) {
		cin >> input;
		if (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8" && input != "9") {
			invalidInput = true;
			cout << "Invalid Input. Try again." << endl;
		}
		else if (board[stoi(input) - 1] != 0) {
			invalidInput = true;
			cout << "That location is already filled. Try again." << endl;
		}
		else
			invalidInput = false;
	}

	int location = stoi(input) - 1;
	board[location] = 1;
	adjustBoardWins(boardWins, 1, location);

	printScreen(board);

	bool win = checkWin(boardWins);
	return win;
}

bool cpuTurn(int *board, int *boardWins, int turnCount) {
	int location = -1;

	int position = rand() % 4;

	//Check if someone can win
	int enemyWin = -1;
	int playerWin = -1;
	for (int i = 8; i < 16; i++) {
		if (boardWins[i] == 2 && boardWins[i - 8] == 0) {
			enemyWin = i;
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (boardWins[i] == 2 && boardWins[i + 8] == 0) {
			playerWin = i;
			break;
		}
	}

	//If you go 2nd and they took a corner, go for the center
	if ((turnCount == 1) && board[4] == 0) //(board[0] == 1 || board[2] == 1 || board[6] == 1 || board[8] == 1))
		location = 4;
	//Win if possible
	else if (enemyWin != -1) {
		location = findWin(board, enemyWin - 8);
	}
	//Block opponent from winning if necessary
	else if (playerWin != -1) {
		location = findWin(board, playerWin);
	}
	//If player is taking corners from going first, play defensive by taking an edge
	else if (turnCount == 3 && board[4] == -1) {
		if ((board[0] == 1 && board[8] == 1) || (board[2] == 1 && board[6] == 1)) {
			if (position == 0)
				location = 1;
			else if (position == 1)
				location = 3;
			else if (position == 2)
				location = 5;
			else
				location = 7;
		}
		//If player takes a corner then take an opposing edge
		else if (board[0] == 1 && board[5] == 1) {
			location = 1;
		}
		else if (board[0] == 1 && board[7] == 1) {
			location = 3;
		}
		else if (board[2] == 1 && board[3] == 1) {
			location = 1;
		}
		else if (board[2] == 1 && board[7] == 1) {
			location = 5;
		}
		else if (board[6] == 1 && board[1] == 1) {
			location = 3;
		}
		else if (board[6] == 1 && board[5] == 1) {
			location = 7;
		}
		else if (board[8] == 1 && board[3] == 1) {
			location = 7;
		}
		else if (board[8] == 1 && board[1] == 1) {
			location = 5;
		}
	}

	//Prediction/Preemptive Block or win
	//Prioritize corners
	else {
		//Pick the corner with the most empty, adjacent edge squares
		int corner0 = 0, corner2 = 0, corner6 = 0, corner8 = 0;
		if (board[1] == 0) {
			corner0++;
			corner2++;
		}
		if (board[3] == 0) {
			corner0++;
			corner6++;
		}
		if (board[5] == 0) {
			corner2++;
			corner8++;
		}
		if (board[7] == 0) {
			corner6++;
			corner8++;
		}

		for (int i = 2; i >= 0; i--) {
			if (corner0 == i && board[0] == 0) {
				location = 0;
				break;
			}
			else if (corner2 == i && board[2] == 0) {
				location = 2;
				break;
			}
			else if (corner6 == i && board[6] == 0) {
				location = 6;
				break;
			}
			else if (corner8 == i && board[8] == 0) {
				location = 8;
				break;
			}
		}
	}

	//If somehow none of the above cases work out and no location has been chosen, all available locations are equally good choices.
	//This prevents the program from replacing a square that already has a value in it.
	if(location == -1) {
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) {
				location = i;
				break;
			}
		}
	}

	board[location] = -1;
	printScreen(board);
	adjustBoardWins(boardWins, -1, location);
	bool win = checkWin(boardWins);
	return win;
}

void printScreen(int *board) {
	string output[9];
	for (int i = 0; i < 9; i++) {
		if (board[i] == -1)
			output[i] = "O";
		else if (board[i] == 1)
			output[i] = "X";

		//board[i] == 0
		else {
			int locationNum = i + 1;
			output[i] = to_string(locationNum); 
		}
	}

	cout << " " << output[0] << " | " << output[1] << " | " << output[2] << endl
		<< "-----------" << endl
		<< " " << output[3] << " | " << output[4] << " | " << output[5] << endl
		<< "-----------" << endl
		<< " " << output[6] << " | " << output[7] << " | " << output[8] << endl
		<< endl;
		    
}

void adjustBoardWins(int *boardWins, int user, int location) {
	int turn = 0;
	if (user == 1)
		turn = 0;
	else if (user == -1)
		turn = 8;
	switch (location) {
		case 0: 
			boardWins[0 + turn]++;
			boardWins[3 + turn]++;
			boardWins[6 + turn]++;
			break;
		case 1: 
			boardWins[0 + turn]++;
			boardWins[4 + turn]++;
			break;
		case 2:
			boardWins[0 + turn]++;
			boardWins[5 + turn]++;
			boardWins[7 + turn]++;
			break;
		case 3:
			boardWins[1 + turn]++;
			boardWins[3 + turn]++;
			break;
		case 4:
			boardWins[1 + turn]++;
			boardWins[4 + turn]++;
			boardWins[6 + turn]++;
			boardWins[7 + turn]++;
			break;
		case 5:
			boardWins[1 + turn]++;
			boardWins[5 + turn]++;
			break;
		case 6:
			boardWins[2 + turn]++;
			boardWins[3 + turn]++;
			boardWins[7 + turn]++;
			break;
		case 7: 
			boardWins[2 + turn]++;
			boardWins[4 + turn]++;
			break;
		default:
			boardWins[2 + turn]++;
			boardWins[5 + turn]++;
			boardWins[6 + turn]++;
	}
		
}


bool checkWin(int *boardWins) {

	for (int i = 0; i < 16; i++) {
		if (boardWins[i] == 3) {
				return true;
		}
	}

	return false;
}

//Using the valid Win condition, find the position to play
int findWin(int *board, int winCondition) {
	int locA, locB, locC;
	switch (winCondition) {
	case 0:
		locA = 0;
		locB = 1;
		locC = 2;
		break;
	case 1:
		locA = 3;
		locB = 4;
		locC = 5;
		break;
	case 2:
		locA = 6;
		locB = 7;
		locC = 8;
		break;
	case 3:
		locA = 0;
		locB = 3;
		locC = 6;
		break;
	case 4:
		locA = 1;
		locB = 4;
		locC = 7;
		break;
	case 5:
		locA = 2;
		locB = 5;
		locC = 8;
		break;
	case 6:
		locA = 0;
		locB = 4;
		locC = 8;
		break;
	default:
		locA = 2;
		locB = 4;
		locC = 6;
		break;
	}
	if (board[locA] == 0)
		return locA;
	else if (board[locB] == 0)
		return locB;
	else
		return locC;
}
