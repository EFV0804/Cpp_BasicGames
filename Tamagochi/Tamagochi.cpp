#include"Tamagochi.h"
#include<iostream>
#include<random>
using std::cout;
using std::endl;

Tamagochi::Tamagochi(const string& pName)
{
	name = pName;
	hunger = 5;
	boredom = 5;
	facts;
}
void Tamagochi::passTime()
{
	hunger++;
	boredom++;
}
void Tamagochi::talk()
{
	if (hunger < 5)
	{
		cout <<name << " says: I'm a bit peckish, no big deal." << endl;
		cout << name << " doesn't need you, worthless human." << endl;
	}
	else if (hunger >= 5 && hunger <= 7)
	{
		cout << name<< " says: I'm hungry, I need to eat. Soon" << endl;
		cout << name << " is just being needy. Ignore it." << endl;
	}
	else if (hunger > 7)
	{
		cout <<name<< " says: I'm starving, I'm gonna eat myself soon." << endl;
		cout << name << " really needs your help. But you don't have to help it." << endl;
	}
	if (boredom < 5)
	{
		cout << name << " says: I'm a bit bored, but that's ok, I've got work to do anyways" << endl;
		cout << name << " is lying, it's unemployed and completly relies on you to provide." << endl;
	}
	else if (boredom >= 5 && boredom <= 7)
	{
		cout << name<<" says: "<<facts[rand()%9] << endl;
		cout << name << " is gonna keep giving useless facts, unless you entertain it." << endl;
	}
	else if (boredom > 7)
	{
		cout <<name<< "says: I have started to grasp my own mortality." << endl;
		cout <<"You might want to play with "<< name << " before it starts quoting Nietzsche..." << endl;
	}
	passTime();
}
void Tamagochi::play()
{
	boredom = boredom -3;
	passTime();
}
void Tamagochi::eat()
{
	hunger= hunger - 3;
	passTime();
}
int Tamagochi::mood()
{
	return hunger + boredom;
}
