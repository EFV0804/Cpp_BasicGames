#include<iostream>
#include<string>
#include "Tamagochi.h"
#include"Farm.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
void interactionChoices(string& playerChoice);
int main(int argc, char** argv)
{
	bool quit = false;
	string playerChoice;
	Tamagochi tamagochiA = Tamagochi("Richard");
	Tamagochi tamagochiB = Tamagochi("Willy");
	Tamagochi* pTamagochiA = nullptr;
	pTamagochiA = &tamagochiA;
	Tamagochi* pTamagochiB = nullptr;
	pTamagochiB = &tamagochiB;
	cout << tamagochiA.getBoredom() << endl;
	cout << tamagochiA.getHunger() << endl;
	Farm farmA = Farm();
	farmA.add(pTamagochiA);
	farmA.add(pTamagochiB);
	farmA.rollCall();


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
		else if (playerChoice == "pass")
		{
			cout << tamagochiA.name << " stares at you blankly." << endl;
			tamagochiA.passTime();
		}
		else if (playerChoice == "quit")
		{
			quit = true;
		}
	}
}
void interactionChoices(string& playerChoice)
{
	cout << "Do you want to listen to your Tamagochi, feed it, play with it, pass some time or quit the game?" << endl;
	cout << "Please type your choice (listen, feed, play, pass, quit)" << endl;
	cin >> playerChoice;
}