#pragma once
#include<SDL.h>
class Ball
{
public:
	Ball(int pX, int pY, int pW, int pH);
	Ball();
	~Ball();
	SDL_Rect toRect();
	void draw(SDL_Renderer* renderer);

private:
	int x;
	int y;
	int w;
	int h;
};