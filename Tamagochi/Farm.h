#pragma once
#include<vector>
#include "Tamagochi.h"
using std::vector;

class Farm
{
private:

public:
	Farm();
	void add(Tamagochi tamagochi);
	void rollCall();
	vector<Tamagochi> tamagochis;
};