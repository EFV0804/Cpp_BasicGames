#pragma once
#include<SDL.h>

class Brick
{
public:
	Brick();
	~Brick();
	SDL_Rect toRect();
	void draw();
	void update();
private:
	int x;
	int y;
	int w;
	int h;
};