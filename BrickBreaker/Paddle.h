#pragma once
#include<SDL.h>

class Paddle
{
public:
	Paddle();
	~Paddle();
	SDL_Rect toRect();
	void update();
	void draw();
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