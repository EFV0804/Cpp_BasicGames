#pragma once
#include<SDL.h>
#include"Renderer.h"


class Ship
{
public:
	Ship();
	Ship(int pX, int pY, int pW, int pH);
	SDL_Rect toRect();
	void draw(Renderer* renderer);
	void update();
	void setPos(int xP, int yP);


private:
	//local position
	int lX;
	int lY;
	//General position
	int x;
	int y;

	int w;
	int h;

};