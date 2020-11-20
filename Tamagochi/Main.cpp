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


	//Tamagochis creation
	Tamagochi tamagochiA = Tamagochi("Richard");
	Tamagochi tamagochiB = Tamagochi("Willy");

	//pointers to Tamagochis
	Tamagochi* pTamagochiA = nullptr;
	pTamagochiA = &tamagochiA;
	Tamagochi* pTamagochiB = nullptr;
	pTamagochiB = &tamagochiB;


	Farm farmA = Farm();
	farmA.add(tamagochiA);
	farmA.add(tamagochiB);

	cout << "Your Tamagochi farm contains " << farmA.tamagochis.size() << " tamgochis. Here are their names: " << endl;
	farmA.rollCall();
	cout << tamagochiA.name<< "'s hunger level is: "<< tamagochiA.getBoredom() << endl;
	cout << tamagochiA.name << "'s boredom level is: " << tamagochiA.getHunger() << endl;
	cout << tamagochiB.name << "'s hunger level is: " << tamagochiB.getBoredom() << endl;
	cout << tamagochiB.name << "'s boredom level is: " << tamagochiB.getHunger() << endl;

	while (!quit)
	{

		interactionChoices(playerChoice);
		if (playerChoice == "listen")
		{
			cout << "Which Tamagochi do you want to listen to? Please type in your answer." << endl;
			farmA.rollCall();
			cin >> playerChoice;
			for (int i = 0; i < farmA.tamagochis.size(); i++)
			{
				if (playerChoice == farmA.tamagochis.at(i).name)
				{
					farmA.tamagochis.at(i).talk();
				}
			}
		}
		else if (playerChoice == "feed")
		{
			cout << "Which Tamagochi do you want to feed? Please type in your answer." << endl;
			farmA.rollCall();
			cin >> playerChoice;
			for (int i = 0; i < farmA.tamagochis.size(); i++)
			{
				if (playerChoice == farmA.tamagochis.at(i).name)
				{
					farmA.tamagochis.at(i).eat();
				}
			}
		}
		else if (playerChoice == "play")
		{
			cout << "Which Tamagochi do you want to listen to? Please type in your answer." << endl;
			farmA.rollCall();
			cin >> playerChoice;
			for (int i = 0; i < farmA.tamagochis.size(); i++)
			{
				if (playerChoice == farmA.tamagochis.at(i).name)
				{
					farmA.tamagochis.at(i).play();
				}
			}
		}
		else if (playerChoice == "pass")
		{
			cout << tamagochiA.name << " stares at you blankly." << endl;
			tamagochiA.passTime();
		}
		else if (playerChoice == "create")
		{
			cout << "Please enter a name for your new Tamagochi." << endl;
			cin >> playerChoice;
			Tamagochi tamagochiC = Tamagochi(playerChoice); //Should probably add dynamic name for the object, but it seems to work like this.
			farmA.add(tamagochiC);
			cout << "A new Tamagochi named " << tamagochiC.name << " has been added to your farm." << endl;
			cout << "Your farm now contains "<< farmA.tamagochis.size() << " tamgochis. Here are their names: " << endl;
			farmA.rollCall();
		}
		else if (playerChoice == "quit")
		{
			quit = true;
		}
	}
}
void interactionChoices(string& playerChoice)
{
	cout << "Do you want to listen to your Tamagochi, feed it, play with it, pass some time, create a new Tamagochi or quit the game?" << endl;
	cout << "Please type your choice (listen, feed, play, pass, create, quit)" << endl;
	cin >> playerChoice;
}