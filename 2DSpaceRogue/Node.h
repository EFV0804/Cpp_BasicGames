#pragma once
#include"Renderer.h"
#include"Vector2.h"
#include<vector>
#include<SDL.h>
#include <stdio.h>  
#include <stdlib.h>

using std::vector;


class Node
{
public:
	enum Type
	{
		Undefined,
		Start,
		End,
		Uncharted,
		Civilised,
		Asteroid,
		Stranded,
		Trade,
		Wreck,
		Live
	};
	Node();
	~Node() {};
	Node(Vector2 vec) : pos(vec) {};

	void setLocType(int pType) { locType = pType; }
	void setPos(float pX, float pY) { pos.set(pX, pY); }
	/*void setIndex(int pIndex){index = pIndex;}*/

	float getX() { return pos.getX(); }
	float getY() { return pos.getY(); }
	Vector2 getPos() { return pos; }
	int getLocType() { return locType; }
	vector <Node*> getNeighbours() { return neighbours; }
	Node* getNeighbour(int i) { return neighbours.at(i); } //unused but could be usuful?
	/*int getIndex(){return index;}*/

	void addNeighbour(Node* neighbour);
	SDL_Rect toRect();
	void handleInputs(SDL_Event* e);
	void draw(Renderer* renderer);
	void drawEdges(Renderer* renderer);

	bool isHovered = false;
	bool isClicked = false;
	bool isSelected = false;

private:


	Vector2 pos;
	int w = 20;
	int h = 20;
	vector <Node*> neighbours;
	int locType = Undefined;
	/*int index; */

};

//Gen map types:
//1 = start
//2 = end
//3 = Uncharted
//4 = Civilised
//5 = Asteroid field

//LocalMap node types:
//#6 = stranded ship;
//#7 = Trade Beacon;
//#8 = Wreckage;
//#9 = Live ship;
