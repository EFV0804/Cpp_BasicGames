#include<iostream>
#include<string>
#include "Tamagochi.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
void interactionChoices(string& playerChoice);
int main(int argc, char** argv)
{
	bool quit = false;
	string playerChoice;
	Tamagochi tamagochiA;

	cout << "Please pick a name for your new very needy and completly useless pet." << endl;
	cin >> tamagochiA.name;

	while (!quit)
	{
		interactionChoices(playerChoice);
		if (playerChoice == "listen")
		{
			tamagochiA.talk();
		}
		else if (playerChoice == "feed")
		{
			tamagochiA.eat();
		}
		else if (playerChoice == "play")
		{
			tamagochiA.play();
		}
		else if (playerChoice == "quit")
		{
			quit = true;
		}
	}
}
void interactionChoices(string& playerChoice)
{
	cout << "Do you want to listen to your Tamagochi, feed it, play with it or quit the game?" << endl;
	cout << "Please type your choice (listen, feed, play, quit)" << endl;
	cin >> playerChoice;
}