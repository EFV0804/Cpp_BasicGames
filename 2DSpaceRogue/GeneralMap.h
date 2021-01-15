#pragma once
#include<vector>
#include<SDL.h>
#include<array>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include"LocalMap.h"
#include "Renderer.h"
#include"Ship.h"


using std::vector;
using std::array;

class GeneralMap
{
public:
	GeneralMap();
	~GeneralMap() {};
	void load();
	void addNode(int i, float x, float y);
	void addEdge(int u, int v);
	void generateMap();
	void generateLocalMap();
	void generateType();
	void generateEdges();
	void handleInputs(SDL_Event* e);
	void draw(Renderer* renderer);
	void setCurrentMap(LocalMap* localMap);
	LocalMap* getCurrentMap() { return currentMap; }
private:
	int numNodes = 16;
	vector <LocalMap*> locMapVec;
	LocalMap* currentMap = nullptr;
	vector <Node*> genMapGridVec;
	Ship ship;
	array <array<float, 2>, 16> coord
	{ {
		{50,50},
		{80,50},
		{110,50},
		{140,50},
		{50,80},
		{80,80},
		{110,80},
		{140,80},
		{50,110},
		{80,110},
		{110,110},
		{140,110},
		{50,140},
		{80,140},
		{110,140},
		{140,140}
	} };
	
};