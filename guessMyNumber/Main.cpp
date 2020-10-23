#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv)
{
	int Num = 10;
	int playerGuess;
	int guessCount = 0; 
	bool success = false;

	while (!success)
	{
		cout << "Guess my number." << endl; //could be made into a function?
		cin >> playerGuess;
		++guessCount;

		if (playerGuess == Num)
		{
			if (guessCount == 1)
			{
				cout << "Well done! I took you " << guessCount << " guess to find my number."<< endl;
				success = true;
			}
			else
			{
				cout << "Well done! I took you " << guessCount << " guesses to find my number." << endl;
				success = true;
			}
		}
		else if (playerGuess > Num)
		{
			cout << "My number is less than " << playerGuess << endl;
		}
		else
		{
			cout << "My number is greater than " << playerGuess << endl;
		}
	}

	return 0;
}