#pragma once
#include<SDL.h>
#include"InputState.h"


class Paddle
{
public:
	Paddle();
	Paddle(int pX, int pY, int pH, int pW, int pSpeedY);
	void draw(SDL_Renderer* renderer);
	SDL_Rect toRect();
	void update(InputState* inputState, int SCREEN_HEIGHT);
	void moveUp(int SCREEN_HEIGHT);
	void moveDown(int SCREEN_HEIGHT);
	void updateAi(int SCREEN_HEIGHT, int ballY);

private:
	int h;
	int w;
	int x;
	int y;
	int speedY;
};