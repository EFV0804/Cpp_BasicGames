#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::cin;
using std::array;
using std::string;
using std::srand;


void boardInit(array<char, 9>boardValues);
void boardDisplay(array<char,9>boardValuesUpdated);
array<char,9> boardUpdate(int playerTurn, int playerInput, array<char, 9>boardValues);


//char boardUpdate(int playerTurn, int playerInput, char boardValues[8]);

int main(int argc, char** argv)
{
	//display board

	array<char, 9>boardValues{'0','1', '2', '3', '4', '5', '6', '7', '8'};

	boardInit(boardValues);

	int playerTurn = true; // if true player 1 if playing, ask for input, else AI
	int playerInput;
	cin >> playerInput; //int that we will use an array index
	
	boardValues = boardUpdate(playerTurn, playerInput, boardValues);

	boardDisplay(boardValues);



	//boardGame update raplacing values in the array (identified by player input passed as index), by "o" or "x"
	//boardUpdate(playerTurn, playerInput, boardValues[]);



}


void boardInit(array<char,9>boardValues)
{
	cout << " " << boardValues[0] << " " << "|" << " " << boardValues[1] << " " << "|" << " " << boardValues[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[3] << " " << "|" << " " << boardValues[4] << " " << "|" << " " << boardValues[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValues[6] << " " << "|" << " " << boardValues[7] << " " << "|" << " " << boardValues[8] << " " << endl;

}

void boardDisplay(array<char,9>boardValuesUpdated)
{
	cout << " " << boardValuesUpdated[0] << " " << "|" << " " << boardValuesUpdated[1] << " " << "|" << " " << boardValuesUpdated[2] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValuesUpdated[3] << " " << "|" << " " << boardValuesUpdated[4] << " " << "|" << " " << boardValuesUpdated[5] << " " << endl;
	cout << "----" << "---" << "----" << endl;
	cout << " " << boardValuesUpdated[6] << " " << "|" << " " << boardValuesUpdated[7] << " " << "|" << " " << boardValuesUpdated[8] << " " << endl;
}

//boardGame update raplacing values in the array (identified by player input passed as index), by "o" or "x"


array<char,9> boardUpdate(int playerTurn, int playerInput, array<char, 9>boardValues)
{

	if (playerTurn)
	{
		boardValues[playerInput] = 'o'; //replace value of array
		array<char, 9>boardValuesUpdated = boardValues;
		return boardValuesUpdated;
	}
	else
	{
		boardValues[playerInput] = 'x';
		array<char, 9>boardValuesUpdated = boardValues;
		return boardValuesUpdated;
	}
	return boardValues;
}