#pragma once
#include<SDL.h>

class Brick
{
public:
	Brick(int pX, int pY);
	~Brick();
	SDL_Rect toRect();
	void draw(SDL_Renderer* renderer);
	void update();

private:
	int x;
	int y;
	int w;
	int h;
};