#include"Ball.h"

Ball::Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY)
	:x(pX), y(pY), w(pW), h(pH), speedX(pSpeedX), speedY(pSpeedY)
{

}
Ball::Ball()
	:x(0), y(0), w(32), h(32), speedX(6), speedY(6)
{
}

Ball::~Ball()
{

}
SDL_Rect Ball::toRect()
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Ball::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Ball::update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	x += speedX;
	y += speedY;
	if (y<0)
	{
		speedY *= -1;
		y = 0;
	}
	if (y > (SCREEN_HEIGHT - h))
	{
		speedY *= -1;
		y = (SCREEN_HEIGHT - h);
	}
	if (x<0)
	{
		speedX *= -1;
		x = 0;
	}
	if (x > (SCREEN_WIDTH - w))
	{
		speedX *= -1;
		x = (SCREEN_WIDTH - w);
	}
}