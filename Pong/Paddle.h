#pragma once
#include<SDL.h>

class Paddle
{
public:
	Paddle();
	Paddle(int pH, int pW, int pX, int pY, int pSpeedY);
	void draw(SDL_Renderer* renderer);
	SDL_Rect toRect();
private:
	int h;
	int w;
	int x;
	int y;
	int speedY;
};