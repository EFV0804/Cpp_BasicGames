#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::array;
using std::srand;

int main(int argc, char** argv)
{
	array<string,5>words{ "banana", "gigantic", "storm", "serendipity", "global" };


	srand((unsigned int)time(0));
	string randomWord = words[(rand() % 5)];
	string realWordSize = randomWord;
	int wordLength = realWordSize.size();

	for (int i = 0; i < wordLength; i++)
	{
		int letter1 = (rand() % wordLength);
		int letter2 = (rand() % wordLength);

		char temp;
		temp = realWordSize[letter1];
		realWordSize[letter1] = realWordSize[letter2];
		realWordSize[letter2] = temp;

	}

	cout << "Put the letters of a word in the correct order. " << endl;
	cout << realWordSize << endl;
	bool quit = false;
	string playerGuess;

	while (!quit)
	{
		cin >> playerGuess;
		if (playerGuess == randomWord)
		{
			cout << "Congratulations! You guessed correctly. Thank you for playing." << endl;
			quit = true;
		}
		else if (playerGuess == "quit") 
		{
			cout<<"Thanks for trying. The correct answer was: " << randomWord << endl;
			quit = true;
		}
		else
		{
			cout << "Wrong. Guess again." << endl;
		}
	}
	return 0;
}