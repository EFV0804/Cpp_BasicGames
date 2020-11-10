#include"Paddle.h"
#include<SDL.h>
#include"InputState.h"


Paddle::Paddle(int pX, int pY, int pH, int pW, int pSpeedY)
	: x(pX), y(pY), h(pH), w(pW), speedY(pSpeedY)
{

}
Paddle::Paddle() //Default constructor
	:x(0), y(0), h(128), w(32), speedY(6)
{

}
SDL_Rect Paddle::toRect() //creates a rectangle from the values given in constructor
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Paddle::draw(SDL_Renderer* renderer) //Calls toRect() to create a rect and the draws the rectangle.
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Paddle::update(InputState* inputState,  int SCREEN_HEIGHT) //gets bool values from a InputState.h object, value of bool is set in Main -> handleInput()
{
	if (inputState->paddleUp)
	{
		moveUp();
	}
	if (inputState->paddleDown)
	{
		moveDown(SCREEN_HEIGHT);
	}
}
void Paddle::updateAi(int SCREEN_HEIGHT, int ballY) //Checks position of the ball compared to Paddle position, and moveUp or moveDown accordingly
{
	if (ballY < y + h / 4) //if ball.y is in the top quarter of paddle
	{
		moveUp();
	}
	if (ballY > y + h / 4 * 3) //if ball.y is in bottom quarter of paddle
	{
		moveDown(SCREEN_HEIGHT);
	}
}
void Paddle::moveUp()
{
	y -= speedY; //reverse direction
	if (y < 0)
	{
		y = 0; //reset position
	}
}
void Paddle::moveDown(int SCREEN_HEIGHT)
{
	y += speedY;
	if (y > (SCREEN_HEIGHT - h))
	{
		y = (SCREEN_HEIGHT - h);
	}
}