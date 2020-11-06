#pragma once
#include<SDL.h>
class Ball
{
public:
	Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY);
	Ball();
	~Ball();
	SDL_Rect toRect();
	void draw(SDL_Renderer* renderer);
	void update();

private:
	int x;
	int y;
	int w;
	int h;
	int speedX;
	int speedY;
};