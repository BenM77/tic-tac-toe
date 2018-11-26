////////////////////////////////////
// Algorithms: Exam 2
// Tic-Tac-Toe
// Tristan Hildahl and Ben Michael
////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

bool playerTurn(int *board);
bool cpuTurn(int *board);
void printScreen(int *board);
bool checkWin(int *board, int user);

int main() {
	//The 9 squares on the board default to empty: -1 is an O, 1 is an X
	int boardFill[9] = { 0,0,0,0,0,0,0,0,0 };
	int *board = boardFill;

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
			playerWon = playerTurn(board);
		else
			cpuWon = cpuTurn(board);

		playersTurn = !playersTurn;
		turnCount++;
	}

	if (playerWon)
		cout << "Congratulations! You Win!" << endl;
	else if (cpuWon)
		cout << "Too bad, you Lose!";
	else
		"Draw!";

	int wait;
	cin >> wait;

	return 0;
}

bool playerTurn(int *board) {
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

	board[stoi(input) - 1] = 1;

	printScreen(board);

	bool win = checkWin(board, 1);
	return win;
}

bool cpuTurn(int *board) {
	//Win if possible
	if (false) {
		;
	}
	//Block opponent from winning if necessary

	//Prediction/Preemptive Block

	//Optimal Starting Play
	else
		board[0] = -1;

	printScreen(board);

	bool win = checkWin(board, -1);
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

bool checkWin(int *board, int user) {

	if ((board[0] == user && board[1] == user && board[2] == user) ||
		(board[3] == user && board[4] == user && board[5] == user) ||
		(board[6] == user && board[7] == user && board[8] == user) ||
		(board[0] == user && board[3] == user && board[6] == user) ||
		(board[1] == user && board[4] == user && board[7] == user) ||
		(board[2] == user && board[5] == user && board[8] == user) ||
		(board[0] == user && board[4] == user && board[8] == user) ||
		(board[2] == user && board[4] == user && board[6] == user))
		return true;
	else
		return false;
}