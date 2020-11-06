#include"Paddle.h"
#include<SDL.h>
#include"InputState.h"


Paddle::Paddle(int pX, int pY, int pH, int pW, int pSpeedY)
	: x(pX), y(pY), h(pH), w(pW), speedY(pSpeedY)
{

}
Paddle::Paddle()
	:x(0), y(0), h(128), w(32), speedY(6)
{

}
SDL_Rect Paddle::toRect()
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Paddle::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Paddle::update(InputState* inputState,  int SCREEN_HEIGHT)
{
	if (inputState->paddleUp)
	{
		y -= speedY;
		if (y<0)
		{
			y = 0;
		}
	}
	if (inputState->paddleDown)
	{
		y += speedY;
		if (y>(SCREEN_HEIGHT - h))
		{
			y = (SCREEN_HEIGHT - h);
		}
	}
}