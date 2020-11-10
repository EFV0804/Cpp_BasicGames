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
	void horizontalBounce(int xReplace);
	void verticalBounce(int yReplace);
	void setX(int newX);
	int getX() const;
	int getWidth() const;
	int speedX;
	int x;
	int y;

private:

	int w;
	int h;
	int speedY;
};