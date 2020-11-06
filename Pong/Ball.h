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
	void update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	int speedX;
	int x;

private:
	int y;
	int w;
	int h;
	int speedY;
};