#pragma once
#include<vector>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include"Window.h"
#include"Node.h"
#include"Renderer.h"
#include"Vector2.h"

using std::vector;
using std::cout;
using std::endl;


class LocalMap
{
public:
	LocalMap();
	void generateMap();
	Vector2 generateCoord();
	void generateType();
	void generateEdges(Node* currentNode);
	void addNode(Vector2 pos);
	void addEdges(Node* u, Node* v);
	void draw(Renderer* renderer);
	void handleInputs(SDL_Event* e);
	void setType(int pType) { type = pType; }

private:
	int type = Node::Undefined;
	vector <Node*> nodeVec;
	int numNodes = 12;
	bool isSelected = false;
};
