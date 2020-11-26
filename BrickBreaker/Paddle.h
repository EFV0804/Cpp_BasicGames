#pragma once
#include<SDL.h>
#include"InputState.h"

class Paddle
{
public:
	Paddle(int pX, int pY, int pW, int pH, int pSpeedX);
	~Paddle();

	//Creating rectangle to draw to screen
	SDL_Rect toRect();
	void draw(SDL_Renderer* renderer);

	//Getters
	const int getX() {return x;}
	const int getY() {return y;}
	const int getW() {return w;}

	//Movement
	void update(InputState* inputState, const int SCREEN_WIDTH);
	void moveLeft();
	void moveRight(const int SCREEN_WIDTH);

private:
	int y;
	int w;
	int x;
	int h;
	int speedX;
};