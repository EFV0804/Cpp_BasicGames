#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::cin;
using std::array;
using std::string;
using std::srand;

void instructions();
void boardInit(char boardValues); 
void boardDisplay(char pBoardValues); 
char boardUpdate(int playerTurn, int playerInput, char boardValues);

int main(int argc, char** argv)
{

	char boardValues[9] = { '0','1', '2', '3', '4', '5', '6', '7', '8' };
	//char* pBoardValues;
	//pBoardValues = &boardValues[0];


	boardInit(boardValues);
	instructions();


	int playerTurn = 1; // if true player 1 if playing, ask for input, else AI
	int playerInput;
	bool success = false;
	bool quit = false;

	while (success == false || quit == false)
	{

		if (playerTurn == 1 )
		{
			cout << "Player 1, choose a spot to mark: " << endl;
			cin >> playerInput;

			boardDisplay(*boardValues);
			playerTurn = 2;
		}
		else
		{
			cout << "Player 2, choose a spot to mark: " << endl;
			cin >> playerInput;
			boardDisplay(*boardValues);
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
void boardInit(char boardValues)
{
	cout << " " << boardValues[0] << " " << "|" << " " <<boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;

}
void boardDisplay(char boardValues)
{
	cout << " " << boardValues[0] << " " << "|" << " " << boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;
}
char boardUpdate(int playerTurn, int playerInput, char boardValues)
{

	if (playerTurn)
	{
		boardValues[playerInput] = 'o'; //replace value of array
		 //create new array whith new values of boardValues
		return boardValues; //returns new array
	}
	else
	{
		boardValues[playerInput] = 'x';
		return boardValues;
	}
	return boardValues;
} //boardUpdate raplacing values in the array ( value identified by player input passed as index), by "o" or "x")