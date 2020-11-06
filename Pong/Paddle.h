#pragma once
#include<SDL.h>
#include"InputState.h"


class Paddle
{
public:
	Paddle();
	Paddle(int pH, int pW, int pX, int pY, int pSpeedY);
	void draw(SDL_Renderer* renderer);
	SDL_Rect toRect();
	void update(InputState* inputState, int SCREEN_HEIGHT);

private:
	int h;
	int w;
	int x;
	int y;
	int speedY;
};