#pragma once
#include<SDL.h>

class Ball
{
public:
	Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY);
	~Ball();
	SDL_Rect toRect();
	void verticalBounce(int yReplace);
	void horizontalBounce(int xReplace);
	void update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void draw(SDL_Renderer* renderer);

private:
	int x;
	int y;
	int w;
	int h;
	int speedY;
	int speedX;
};