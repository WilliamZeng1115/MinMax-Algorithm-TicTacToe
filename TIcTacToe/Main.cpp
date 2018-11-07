#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int makeBestMovePlayer(char board[][3], int size, int sol[], int counter);

void printBoard(char board[][3], int size) {
	for (int i = 0; i < size; ++i)
	{
		cout << "|";
		for (int j = 0; j < size; ++j)
		{
			cout << board[i][j] << '|';
		}
		cout << endl;
		cout << "--------" << endl;
	}
	
}

int checkBoard(char board[][3], int size) {
	for (int i = 0; i < size; i++) {
		if (board[i][0] == 'x' && board[i][1] == 'x' && board[i][2] == 'x') {
			return 1;
		}
		else if (board[i][0] == 'o' && board[i][1] == 'o' && board[i][2] == 'o') {
			return -1;
		}
		if (board[0][i] == 'x' && board[1][i] == 'x' && board[2][i] == 'x') {
			return 1;
		}
		else if (board[0][i] == 'o' && board[1][i] == 'o' && board[2][i] == 'o') {
			return -1;
		}
	}
	if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') {
		return 1;
	}
	else if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o') {
		return -1;
	}
	if (board[2][0] == 'x' && board[1][1] == 'x' && board[0][2] == 'x') {
		return 1;
	}
	else if (board[2][0] == 'o' && board[1][1] == 'o' && board[0][2] == 'o') {
		return -1;
	}
	/*int space = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == ' ')
				space++;
		}
	}
	if (space == 0)
		return 0;*/
	return 0;
}

int makeBestMoveComputer(char board[][3], int size, int sol[], int counter) {
	int maxValue = -10;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = 'x';
				//cout << endl;
				//printBoard(board, size);
				int temp = checkBoard(board, size);
				if (temp == 1) {
					if (maxValue < temp) {
						maxValue = temp;
						sol[0] = i;
						sol[1] = j;
						board[i][j] = ' ';
						goto stop;
					}
				}
				else if (counter >= 0) {
					int tempBest = makeBestMovePlayer(board, size, sol, counter - 1);
					if (tempBest == 10) {
						maxValue = 0;
						sol[0] = i;
						sol[1] = j;
					}
					else if (maxValue < tempBest) {
						maxValue = tempBest;
						sol[0] = i;
						sol[1] = j;
					}
				}
				else {
					if (maxValue < 0) {
						maxValue = 0;
						sol[0] = i;
						sol[1] = j;
					}
				}
				board[i][j] = ' ';
			}
		}
	}
	stop:
	return maxValue;
}

int makeBestMovePlayer(char board[][3], int size, int sol[], int counter) {
	int minValue = 10;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = 'o';
				//cout << endl;
				//printBoard(board, size);
				int temp = checkBoard(board, size);
				if (temp == -1) {
					if (minValue > temp) {
						minValue = temp;
						board[i][j] = ' ';
						goto stop;
					}
				}
				else if (counter > 0) {
					int tempBest = makeBestMoveComputer(board, size, sol, counter - 1);
					if(tempBest == -10){
						minValue = 0;
					}
					else if (minValue > tempBest) {
						minValue = tempBest;
					}
				}
				else {
					if (minValue > 0) {
						minValue = 0;
					}
				}
				board[i][j] = ' ';
			}
		}
	}
stop:
	//cout << "Min value: " << minValue << endl;
	return minValue;
}

int main() {
	int const static size = 3;
	char board[][size] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
	//char board[][size] = { { 'o', ' ', 'o' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	//char board[][size] = { { 'o', ' ', ' ' },{ ' ', 'o', ' ' },{ ' ', ' ', ' ' } };
	//char board[][size] = { { 'x', ' ', 'o' },{ ' ', ' ', ' ' },{ 'x', ' ', 'o' } };
	//char board[][size] = { { ' ', 'o', ' ' },{ ' ', ' ', ' ' },{ ' ', 'o', ' ' } };
	//char board[][size] = { { ' ', ' ', ' ' },{ 'o', ' ', 'o' },{ ' ', ' ', ' ' } };
	//char board[][size] = { { 'o', ' ', 'x' },{ ' ', ' ', ' ' },{ 'o', ' ', 'x' } };
	//char board[][size] = { { 'x', ' ', 'o' },{ ' ', ' ', ' ' },{ ' ', ' ', 'o' } };
	
	int game = 1;
	int turn = 0;
	char player = 'o';
	char computer = 'x'; 
	int check = 0;
	int slot = 9;
	printBoard(board, size);

	int sol[2];
	cout << makeBestMoveComputer(board, size, sol, 1) << endl;
	cout << sol[0] << endl;
	cout << sol[1] << endl;

	while (game) {
		if (turn % 2 == 0) {
			cout << "Your turn" << endl;
			cout << "Enter the row: ";
			int row = 5;
			while (row > 3 || row <= 0) {
				cout << "Enter a number between 1 - 3" << endl;
				cin >> row;
			}
			cout << "Enter the column: ";
			int col = 5;
			while (col > 3 || col <= 0) {
				cout << "Enter a number between 1 - 3" << endl;
				cin >> col;
			}
			if (board[row - 1][col - 1] == ' ') {
				board[row - 1][col - 1] = player;
				slot--;
			}
			else {
				cout << "Move unavaliable" << endl;
				turn--;
				slot++;
			}
		}
		else {
			cout << "Computer's turn" << endl;
			if(makeBestMovePlayer(board, size, sol, 1) == -1)
				makeBestMoveComputer(board, size, sol, 1);
			else makeBestMoveComputer(board, size, sol, 2);
			int row = sol[0];
			int col = sol[1];
			if (turn < 2 && board[1][1] == ' ') {
				row = 1;
				col = 1;
			}
			cout << "Moved at row: " << row + 1 << " and column: " << col + 1 << endl;
			if (board[row][col] == ' ')
				board[row][col] = computer;
			slot--;
		}
		turn++;
		printBoard(board, size);
		check = checkBoard(board, size);
		if (check == -1 || check == 1)
			game = 0; // end game
		if (slot == 0)
			game = 0;
	}
	cout << endl;
	cout << "Game Ended" << endl;
	if (check == 1)
		cout << "Computer wins!!" << endl;
	else if (check == -1)
		cout << "Player wins!!" << endl;
	else if (!check)
		cout << "Tied!!" << endl;
	cout << "Enter any key to continue . . ." << endl;
	int n;
	cin >> n;

	return 0;
}