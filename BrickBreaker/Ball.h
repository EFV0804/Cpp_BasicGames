#pragma once
#include<SDL.h>
#include"Paddle.h"

class Ball
{
public:
	Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY);
	~Ball();
	SDL_Rect toRect();
	void verticalBounce(int yReplace);
	void horizontalBounce(int xReplace);
	void update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, InputState* inputState);
	void draw(SDL_Renderer* renderer);
	void speedSet(int speedYRep, int speedXrep);
	void reset(const int pX, const int pY);
	void dirSet(InputState* inputState);
	bool isBallReset = false; // used in Main inputHandle()

	//TESTING
	void reverseSpeed(int& speed);
	int speedX;


	int y; //used in Main update()
	int h; //used in Main update()
	int w; //used in Main update()
private:
	int x;
	int speedY;
};