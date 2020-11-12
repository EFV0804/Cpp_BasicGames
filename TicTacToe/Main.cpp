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
void boardInit(array<char, 9> boardValues);
array<char, 9> boardUpdate(int playerTurn, int playerInput, array<char, 9>& boardValues);
array<char, 9> boardUpdateCPU(int playerTurn, array<char, 9>& boardValues, int cpuInput);
bool isSuccessPlayerO(array<char, 9> boardValues, array<array<int, 3>, 8> winCons, char playerO);
bool isSuccessPlayerX(array<char, 9> boardValues, array<array<int, 3>, 8> winCons, char playerX);
//bool isTie(array<char, 9> boardValues, array<array<int, 3>, 8> winCons, char playerO, char playerX);
int cpuMove(array<array<int, 3>, 8> winCons, array<char, 9> boardValues, char playerX, char playerO, int& cpuInput);


int main(int argc, char** argv)
{
	// INITIAL BOARD VALUES + POINTER

	array<char, 9> boardValues = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
	array<array<int, 3>, 8> winCons =
	{ {
	{ 0, 1, 2 },
	{ 0, 3, 6 },
	{ 0, 4, 8 },
	{ 1, 4, 7 },
	{ 3, 4, 5 },
	{ 2, 4, 6 },
	{ 2, 5, 8 },
	{ 6, 7, 8 }
	} };

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
	boardInit(boardValues);

	
	int playerInput;
	int* pPlayerInput = nullptr;
	pPlayerInput = &playerInput;
	int cpuInput;

		//While loop variables
	bool success = false;
	bool quit = false;

		//For loops variables
	int a = 0;
	int i = 0;
	int counter = 0;
	bool tie = false;

	// GAME LOOP
	while (!success/* && !tie*/)
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
				success = isSuccessPlayerO(boardValues, winCons, playerO);
				/*tie = isTie(boardValues, winCons, playerO, playerX);*/
				playerTurn = 2;
		}
		else
		{
			cout << "Computer's turn to play: " << endl;
			/*while (playerInput > 8)
			{
				cout << "Invalid input. Pick a number between 0 and 8" << endl;
				cin >> playerInput;
			}
			while (boardValues[playerInput] == playerO || boardValues[playerInput] == playerX)
			{
				cout << "Sorry already taken, choose again." << endl;
				cin >> playerInput;
			}*/
			cpuMove(winCons, boardValues, playerX, playerO, cpuInput);
			boardUpdateCPU(playerTurn, boardValues, cpuInput);
			boardDisplay(boardValues);
			success = isSuccessPlayerX(boardValues, winCons, playerX);
			/*tie = isTie(boardValues, winCons, playerO, playerX);*/
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
	/*system("cls");*/
	cout << " " << boardValues[0] << " " << "|" << " " << boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;

}
void boardInit(array<char, 9> boardValues)
{
	cout << " " << boardValues[0] << " " << "|" << " " << boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;

}
array<char, 9> boardUpdate(int playerTurn, int playerInput, array<char, 9> &boardValues)
{
	boardValues[playerInput] = 'o'; //replace value of array
	return boardValues; //returns update array
} //boardUpdate replacing values in the array ( value identified by player input passed as index), by "o" or "x")
array<char, 9> boardUpdateCPU(int playerTurn, array<char, 9>& boardValues, int cpuInput)
{
	boardValues[cpuInput] = 'x';
	return boardValues;
}
bool isSuccessPlayerO(array<char, 9> boardValues, array<array<int, 3>, 8> winCons, char playerO)
{
	int a = 0;
	int i = 0;
	int counter = 0;

	for (a = 0; a < 8; a++)
	{
		counter = 0;
		for (i = 0; i < 3; i++)
		{
			if (boardValues[winCons[a][i]] == playerO)
			{
				counter++;
			}
			else
			{
			}
		}
		if (counter == 3)
		{
			cout << "Victory! Congratulations Player 1!" << endl;
			return true;
		}
	}
	return false;
}
bool isSuccessPlayerX(array<char, 9> boardValues, array<array<int, 3>, 8> winCons, char playerX)
{
	int a = 0;
	int i = 0;
	int counter = 0;

	for (a = 0; a < 8; a++)
	{
		counter = 0;
		for (i = 0; i < 3; i++)
		{
			if (boardValues[winCons[a][i]] == playerX)
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
			return true;
		}
	}
	return false;
}
 /*isTie(): do better than counting moves, use cpuMove type loop to check winCons*/
//bool isTie(array<char, 9> boardValues, array<array<int, 3>, 8> winCons,  char playerO, char playerX)
//{
//	int counterO = 0;
//	int counterX = 0;
//	int tied = 0;
//	for (int a = 0; a < 8; a++)
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			if (boardValues[winCons[a][i]] == playerO)
//			{
//				counterO++;
//			}
//			else if (boardValues[winCons[a][i]] == playerX)
//			{
//				counterX++;
//			}
//			else if (counterO == 1 && counterX == 1)
//			{
//				tied++;
//				cout << "tied is : " << tied << endl;
//			}
//			else if (counterO == 2 && counterX == 1)
//			{
//				tied++;
//				cout << "tied is : " << tied << endl;
//			}
//			else if (counterO == 1 && counterX == 2)
//			{
//				tied++;
//				cout << "tied is : " << tied << endl;
//			}
//
//		}
//	}
//	if (tied == 8)
//	{
//		cout << "it's a tie" << endl;
//		return true;
//	}
//}
int cpuMove(array<array<int, 3>, 8> winCons, array<char, 9> boardValues, char playerX, char playerO, int& cpuInput)
{
	// Loop to check for victory moves
	for (int a = 0; a < 8; a++)
	{
		int freeSpot;
		int counterX = 0;
		int counterO = 0;
		for (int i = 0; i < 3; i++)
		{
			if (boardValues[winCons[a][i]] == playerX)
			{
				counterX++;
			}
			else if (boardValues[winCons[a][i]] == playerO)
			{
				counterO++;
			}
			else if ((boardValues[winCons[a][i]] != playerX) && (boardValues[winCons[a][i]] != playerO))
			{
				freeSpot = winCons[a][i];
			}
		}
		if (counterX == 2 && counterO == 0)
		{
			cpuInput = freeSpot;
			return cpuInput;
			break;
		}
		else if (counterO == 2 && counterX == 0)
		{
			cpuInput = freeSpot;
			return cpuInput;
			break;
		}
	}
	// Loop to check for player1 victory moves
	/*for (int a = 0; a < 8; a++)
	{
		int freeSpot;
		int counterX = 0;
		int counterO = 0;
		cout << "current array for P1 victory moves is " << a << endl;
		for (int i = 0; i < 3; i++)
		{
			if (boardValues[winCons[a][i]] == playerO)
			{
				counterO++;
				cout << "counterO is " << counterO << endl;
			}
			else if (boardValues[winCons[a][i]] == playerX)
			{
				counterX++;
				cout << "counterX is " << counterX << endl;
			}
			else if ((boardValues[winCons[a][i]] != playerX) && (boardValues[winCons[a][i]] != playerO))
			{
				freeSpot = winCons[a][i];
				cout << "freeSpot is " << freeSpot << endl;
			}
		}
		if (counterO == 2 && counterX == 0)
		{
			cpuInput = freeSpot;
			cout << "cpuInput is " << cpuInput << endl;
			return cpuInput;
			break;
		}
	}*/
	if (boardValues[4] == '4')
	{
		cpuInput = 4;
	}
	else if (boardValues[0] == '0')
	{
		cpuInput = 0;
	}
	else if (boardValues[2] == '2')
	{
		cpuInput = 2;
	}
	else if (boardValues[6] == '6')
	{
		cpuInput = 6;
	}
	else if (boardValues[8] == '8')
	{
		cpuInput = 8;
	}
	return cpuInput;
	//Take center if available or corners
}