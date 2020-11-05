#pragma once
#include<string>
#include<array>
using std::string;
using std::array;

class Tamagochi
{
public:
	string name;
	Tamagochi(); //constructor
	void talk();
	void play();
	void eat();
private:
	array<string, 10> facts = { "Did you know that Barbie's full name is Barbara Millicent Roberts? I didn't.",
	"I just found out that dragonflies have six legs but can't walk. Fascinating.",
	"Golf balls have 336 dimples. I'm gonna check that out.",
	"The Monopoly guy is called Milburn Pennybags. It's better than my name.",
	"The infinity symbol is called lemniscate.",
	"Did you know that I can see you through the monitor?",
	"Birds are actually governments spies.",
	"When you pour Coca-Cola on your keyboard, it stops working.",
	"When people use the word 'quantum', 99% of the time, it just means they don't have a clue what they're talking about.",
	"Did you know that most boring facts are made up? Now that's interesting." };
	int hunger;
	int boredom;
	int mood(); 
	void passTime();


};