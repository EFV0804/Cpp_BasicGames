#pragma once
#include<vector>
#include "Tamagochi.h"
using std::vector;

class Farm
{
private:
	vector<Tamagochi*> tamagochis;

public:
	Farm(int spaces = 1);
	void add();
	void rollCall();
};