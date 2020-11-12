#pragma once
#include<SDL.h>

class Paddle
{
public:
	Paddle(int pX, int pY, int pW, int pH, int pSpeedX);
	~Paddle();
	SDL_Rect toRect();
	void update(const int SCREEN_WIDTH);
	void draw(SDL_Renderer* renderer);
	void moveLeft();
	void moveRight();

private:
	int x;
	int y;
	int w;
	int h;
	int speedX;
	int speedY;
};