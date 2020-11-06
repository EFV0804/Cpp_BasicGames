#include"Paddle.h"
#include<SDL.h>

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
