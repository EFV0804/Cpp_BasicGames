#include <iostream>
#include <string>
#include <array>
#include <time.h>
#include <random>

using std::cout;
using std::endl;
using std::cin;
using std::array;
using std::string;
using std::srand;

void instructions();
void boardDisplay(array<char, 9> boardValues);
array<char, 9> boardUpdate(int playerTurn, int playerInput, array<char, 9>& boardValues);
bool isSuccessPlayerO(bool* pSuccess, array<char, 9> boardValues, char playerO);
bool isSuccessPlayerX(bool* pSuccess, array<char, 9> boardValues, char playerX);


int main(int argc, char** argv)
{
	// INITIAL BOARD VALUES + POINTER

	array<char, 9> boardValues = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };

	// PLAYER SYMBOLS

	char playerO = 'o';
	char playerX = 'x';

	//INITIALIZE GAME

	instructions();

	srand((unsigned int)time(0)); //randomize starting player
	int playerTurn = rand()%2 + 1;
	int* pPlayerTurn = nullptr;
	pPlayerTurn = &playerTurn;

	cout << "The starting player is Player " << playerTurn <<endl;
	boardDisplay(boardValues);

	// GAME LOOP
	int playerInput;
	int* pPlayerInput = nullptr;
	pPlayerInput = &playerInput;

		//While loop variables
	bool success = false;
	bool* pSuccess = &success;
	bool quit = false;

		//For loops variables
	int a = 0;
	int i = 0;
	int counter = 0;
	bool tie = false;
	bool* pTie = &tie;

	while (*pSuccess == false /*|| *pTie == false*/)
	{
		
		if (playerTurn == 1 )
		{
			cout << "Player 1, choose a spot to mark: " << endl;
			cin >> playerInput;
			while ( playerInput > 8)
			{
				cout << "Invalid input. Pick a number between 0 and 8" << endl;
				cin >> playerInput;
			}
			while (boardValues[playerInput] == playerO || boardValues[playerInput] == playerX )
			{
				cout << "Sorry already taken, choose again." << endl;
				cin >> playerInput;
			}
				boardUpdate(playerTurn, playerInput, boardValues);
				boardDisplay(boardValues);
				isSuccessPlayerO(pSuccess, boardValues, playerO);
				/*isTie();*/
				playerTurn = 2;
		}
		else
		{
			cout << "Player 2, choose a spot to mark: " << endl;
			cin >> playerInput;
			while (playerInput > 8)
			{
				cout << "Invalid input. Pick a number between 0 and 8" << endl;
				cin >> playerInput;
			}
			while (boardValues[playerInput] == playerO || boardValues[playerInput] == playerX)
			{
				cout << "Sorry already taken, choose again." << endl;
				cin >> playerInput;
			}
				boardUpdate(playerTurn, playerInput, boardValues);
				boardDisplay(boardValues);
				isSuccessPlayerX(pSuccess, boardValues, playerX);
				/*isTie();*/
				playerTurn = 1;
		}
	}

}

void instructions()
{
	cout << "TicTacToe rules: " << endl;
	cout << "The goal is to mark 3 contiguous spots horizontally, vertically or diagonally." << endl;
	cout << "Each spot is identified by a number between 0 and 9" << endl;
	cout << "To mark a spot, enter the corresponding number when prompted." << endl;
	cout << "The starting player is chosen at random. The players alternate turns." << endl;
}
void boardDisplay(array<char,9> boardValues)
{
	cout << " " << boardValues[0] << " " << "|" << " " << boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;

}
array<char, 9> boardUpdate(int playerTurn, int playerInput, array<char, 9> &boardValues)
{
	int x;

	if (playerTurn == 1)
	{
		int x = playerInput;
		boardValues[x] = 'o'; //replace value of array
		return boardValues; //returns update array
	}
	else
	{
		int x = playerInput;
		boardValues[x] = 'x';
		return boardValues;
	}
} //boardUpdate raplacing values in the array ( value identified by player input passed as index), by "o" or "x")
bool isSuccessPlayerO(bool* pSuccess, array<char, 9> boardValues, char playerO)
{
	array<array<char, 3>, 8> winCons =
	{ {
	{ boardValues[0], boardValues[1], boardValues[2] },
	{ boardValues[0], boardValues[3], boardValues[6] },
	{ boardValues[0], boardValues[4], boardValues[8] },
	{ boardValues[1], boardValues[4], boardValues[7] },
	{ boardValues[3], boardValues[4], boardValues[5] },
	{ boardValues[2], boardValues[4], boardValues[6] },
	{ boardValues[2], boardValues[5], boardValues[8] },
	{ boardValues[6], boardValues[7], boardValues[8] }
	} };
	int a = 0;
	int i = 0;
	int counter = 0;

	for (a = 0; a < 8; a++)
	{
		counter = 0;
		for (i = 0; i < 3; i++)
		{
			if (winCons[a][i] == playerO)
			{
				counter++;
			}
			else
			{
			}
		}
		if (counter == 3)
		{
			cout << "Victory! Congratulations Player 1" << endl;
			*pSuccess = true;
			break;
		}
	}
	if (!*pSuccess)
	{
		cout << "no victory conditions met" << endl;
	}
	return *pSuccess;
}
bool isSuccessPlayerX(bool* pSuccess, array<char, 9> boardValues, char playerX)
{
	array<array<char, 3>, 8> winCons =
	{ {
	{ boardValues[0], boardValues[1], boardValues[2] },
	{ boardValues[0], boardValues[3], boardValues[6] },
	{ boardValues[0], boardValues[4], boardValues[8] },
	{ boardValues[1], boardValues[4], boardValues[7] },
	{ boardValues[3], boardValues[4], boardValues[5] },
	{ boardValues[2], boardValues[4], boardValues[6] },
	{ boardValues[2], boardValues[5], boardValues[8] },
	{ boardValues[6], boardValues[7], boardValues[8] }
	} };
	int a = 0;
	int i = 0;
	int counter = 0;

	for (a = 0; a < 8; a++)
	{
		counter = 0;
		for (i = 0; i < 3; i++)
		{
			if (winCons[a][i] == playerX)
			{
				counter++;
			}
			else
			{
			}
		}
		if (counter == 3)
		{
			cout << "Victory! Congratulations Player 2!" << endl;
			*pSuccess = true;
			break;
		}
	}
	if (!*pSuccess)
	{
		cout << "no victory conditions met" << endl;
	}
	return *pSuccess;
}
bool isTie(array<char, 9> boardValues, char playerO, char playerX, bool* pTie)
{
	int counter = 0;
	for (int i = 0; 1 < 9; i++)
	{
		if (boardValues[i] = playerO || playerX)
		{
			counter++;
		}
		else
		{
			break;
		}
	}
	if (counter == 9)
	{
		*pTie = true;
		return *pTie;
	}
}