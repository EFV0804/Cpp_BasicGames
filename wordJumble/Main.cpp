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
	array<string, 5>words{ "banana", "gigantic", "storm", "serendipity", "global" };
	array<string, 5 > hints{ "a funky shaped fruit","an adjective to describe the size of something","a weather anomaly", "the positive outcome of luck","a scale used to describe the planet" };

	/*srand((unsigned int)time(0));
	int x = (rand() % 5);
	string randomWord = words[x];
	string realWordSize = randomWord;
	int wordLength = realWordSize.size();
	string hint = hints[x];
	int score = wordLength;

		for (int i = 0; i < wordLength; i++)
		{
			int letter1 = (rand() % wordLength);
			int letter2 = (rand() % wordLength);

			char temp;
			temp = realWordSize[letter1];
			realWordSize[letter1] = realWordSize[letter2];
			realWordSize[letter2] = temp;

		}*/

	cout << "Put the letters of a word in the correct order. " << endl;
	//cout << realWordSize << endl;
	bool quit = false;
	bool playerStatus = false; //Changes if the players get the answer right
	string playerGuess; // player's input

	while (quit == false) //Game loop
	{
		srand((unsigned int)time(0)); //random seed
		int x = (rand() % 5); // generate a random int between 0-5
		string randomWord = words[x];
		string realWordSize = randomWord; // might not be necessary
		int wordLength = realWordSize.size();
		string hint = hints[x];
		int score = wordLength;

		for (int i = 0; i < wordLength; i++)
		{
			int letter1 = (rand() % wordLength);
			int letter2 = (rand() % wordLength);
			char temp;
			temp = realWordSize[letter1];
			realWordSize[letter1] = realWordSize[letter2];
			realWordSize[letter2] = temp;

		}
		cout << realWordSize << endl;
		cin >> playerGuess;


		while (playerStatus == false && quit == false) //Loop to keep player guessing
		{
			if (playerGuess == randomWord)
			{
				cout << "Congratulations! You guessed correctly." << endl;
				cout << "You scored " << score << " points." << endl;
				playerStatus = true;
			}
			else if (playerGuess == "hint")
			{
				cout << "Here's a little help: " << hint << endl;
				score--;
				cin >> playerGuess;
			}
			else if (playerGuess == "quit")
			{
				cout << "Thanks for trying. The correct answer was: " << randomWord << endl;
				quit = true;
			}
			else
			{
				cout << "Wrong. Guess again." << endl;
				cin >> playerGuess;
			}
		}
		if (playerStatus == true ) // option to keep playing with a new word, or to quit.
		{
			cout << "Do you want to play again?" << endl;
			cin >> playerGuess;

			if (playerGuess == "yes" || "Yes") 
			{
				playerStatus = false; // player bet
			}
			else //doesn't quit the loop. Sends back to guessing
			{
				playerStatus = false;
				quit = true;
			}
		}
	}


	return 0;
}