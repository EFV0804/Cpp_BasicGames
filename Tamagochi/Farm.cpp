#include"Farm.h"
#include<iostream>
using std::cout;
using std::endl;

Farm::Farm()
{
	vector <Tamagochi*> tamagochis;
}
void Farm::add(Tamagochi* tamagochi)
{
	tamagochis.push_back(tamagochi);
}
void Farm::rollCall()
{
	for (int i = 0; i < tamagochis.size(); i++)
	{
		cout << tamagochis.at(i) << endl;
	}
}