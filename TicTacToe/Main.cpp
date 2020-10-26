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
void boardDisplay(char* pBoardValues); 
char* boardUpdate(int* playerTurn, int* pPlayerInput, char* pBoardValues);
bool isSuccessPlayerO(bool* pSuccess, char* pWinCons, char playerO);
bool isSuccessPlayerX(bool* pSuccess, char* pWinCons, char playerX);

int main(int argc, char** argv)
{
	char boardValues[9] = { '0','1', '2', '3', '4', '5', '6', '7', '8' };
	char* pBoardValues;
	pBoardValues = &boardValues[0];

	//WINCON CONDITIONALS
	
	char winCons[8][3] =
	{
	{ boardValues[0], boardValues[1], boardValues[2] },
	{ boardValues[3], boardValues[4], boardValues[5] },
	{ boardValues[6], boardValues[7], boardValues[8] },
	{ boardValues[0], boardValues[4], boardValues[8] },
	{ boardValues[2], boardValues[4], boardValues[6] },
	{ boardValues[0], boardValues[3], boardValues[6] },
	{ boardValues[1], boardValues[4], boardValues[7] },
	{ boardValues[2], boardValues[5], boardValues[8] }
	};
	char* pWinCons = nullptr;
	pWinCons = &winCons[0][0];

	char playerO = 'o';
	char playerX = 'x';

	//INITIALIZE GAME

	boardDisplay(pBoardValues);
	instructions();

	srand((unsigned int)time(0)); //randomize starting player
	int playerTurn = rand()%2 + 1; // if true player 1 if playing, ask for input, else AI
	int* pPlayerTurn = nullptr;
	pPlayerTurn = &playerTurn;

	cout << "The starting player is Player " << playerTurn << endl;

	int playerInput;
	int* pPlayerInput = nullptr;
	pPlayerInput = &playerInput;

	bool success = false;
	bool* pSuccess = &success;
	bool quit = false;


	//GAME LOOP
	while (success == false || quit == false)
	{
		boardDisplay(pBoardValues);

		if (playerTurn == 1 )
		{
			cout << "Player 1, choose a spot to mark: " << endl;
			cin >> playerInput;

			if (boardValues[playerInput] == 'x')
			{
				cout << "Sorry already taken, choose again." << endl;
				cin >> playerInput;
				boardUpdate(pPlayerTurn, pPlayerInput, pBoardValues);
				playerTurn = 2;
			}
			else
			{
				boardUpdate(pPlayerTurn, pPlayerInput, pBoardValues);
				isSuccessPlayerO(pSuccess, pWinCons, playerO);
				playerTurn = 2;
			}
		}
		else
		{
			cout << "Player 2, choose a spot to mark: " << endl;
			cin >> playerInput;

			if (boardValues[playerInput] == 'o')
			{
				cout << "Sorry already taken, choose again." << endl;
				cin >> playerInput;
				boardUpdate(pPlayerTurn, pPlayerInput, pBoardValues);
				playerTurn = 1;
			}
			else
			{
				boardUpdate(pPlayerTurn, pPlayerInput, pBoardValues);
				playerTurn = 1;
			}
		}
		//winConUpdate()
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
void boardDisplay(char* pBoardValues)
{
	cout << " " << pBoardValues[0] << " " << "|" << " " << pBoardValues[1] << " " << "|" << " " << pBoardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << pBoardValues[3] << " " << "|" << " " << pBoardValues[4] << " " << "|" << " " << pBoardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << pBoardValues[6] << " " << "|" << " " << pBoardValues[7] << " " << "|" << " " << pBoardValues[8] << " " << endl;

}
char* boardUpdate(int* playerTurn, int* pPlayerInput, char* pBoardValues)
{

	if (*playerTurn == 1)
	{
		int x = *pPlayerInput;
		pBoardValues[x] = 'o'; //replace value of array
		return pBoardValues; //returns update array
	}
	else
	{
		int x = *pPlayerInput;
		pBoardValues[x] = 'x';
		return pBoardValues;
	}
} //boardUpdate raplacing values in the array ( value identified by player input passed as index), by "o" or "x")
bool isSuccessPlayerO(bool* pSuccess, char* pWinCons, char playerO)
{
	while (*pSuccess == false)
	{
		for (int a = 0; a < 8;) //variable to increment first index
		{
			int counter = 0;
			for (int* i = 0; i < 3;) //variable to increment second index
			{
				if (pWinCons[a][i] == playerO && *pSuccess == false)
				{
					i++;
					counter++;
					cout << "counter = " << counter << endl;

					if (counter == 3)
					{
						*pSuccess = true;
						cout << pWinCons[a][i] << " winning condition is met" << endl;
						return pSuccess;
					}
				}
				else
				{
					a++;
				}
			}
		}
	}
}
bool isSuccessPlayerX(bool* pSuccess, char* pWinCons, char playerX)
{
	while (*pSuccess == false)
	{
		for (int a = 0; a < 8;) //variable to increment first index
		{
			int counter = 0;
			for (int* i = 0; *i < 3;) //variable to increment second index
			{
				if (pWinCons[a][i] == playerX && *pSuccess == false)
				{
					i++;
					counter++;
					cout << "counter = " << counter << endl;

					if (counter == 3)
					{
						*pSuccess = true;
						cout << pWinCons[a][i] << " winning condition is met" << endl;
					}
				}
				else
				{
					a++;
				}
			}
		}
	}
}