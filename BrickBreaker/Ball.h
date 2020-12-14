#pragma once
#include<SDL.h>
#include"Paddle.h"
#include"Renderer.h"

class Ball
{
public:
	Ball();
	Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY);
	~Ball();

	//Create rectagle to draw on screen
	SDL_Rect toRect();
	void draw(Renderer* renderer);

	//Getters
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return w; }
	int getH() { return h; }
	int getSpeedX() { return speedX; }
	int getSpeedY() { return speedY; }

	//Setters
	void setX(int pX) { x = pX; }
	void setY(int pY) { y = pY; }

	//Reverses X or Y speed
	void verticalBounce();
	void horizontalBounce();

	//To make the ball bounce on screen edges
	void update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, InputState* inputState);

	// To reset ball after it is lost
	bool isBallReset = true;
	void reset(const int pX, const int pY);
	void dirSet(InputState* inputState);

private:
	int x;
	int y;
	int h;
	int w;
	int speedX;
	int speedY;
};