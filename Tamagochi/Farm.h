#pragma once
#include<vector>
#include "Tamagochi.h"
using std::vector;

class Farm
{
private:
	vector<Tamagochi*> tamagochis;

public:
	Farm();
	void add(Tamagochi* tamagochi);
	void rollCall();
};