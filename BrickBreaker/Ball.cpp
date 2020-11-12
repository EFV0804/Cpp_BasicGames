#include "Ball.h"

Ball::Ball(int pX, int pY, int pW, int pH, int pSpeedX, int pSpeedY)
	:x(pX), y(pY), w(pW), h(pH), speedX(pSpeedX), speedY(pSpeedY)
{

}
Ball::~Ball()
{

}
SDL_Rect Ball::toRect()
{
	SDL_Rect rect{ x, y, w, h };
	return rect;
}
void Ball::update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	x += speedX;
	y += speedY;
	if (x < 0)
	{
		horizontalBounce(0);
	}
	if (x > SCREEN_WIDTH-w)
	{
		horizontalBounce(SCREEN_WIDTH - w);
	}
	if (y < 0)
	{
		verticalBounce(0);
	}
	if (y > SCREEN_HEIGHT-h)
	{
		verticalBounce(SCREEN_HEIGHT-h);
	}
}
void Ball::verticalBounce(int yReplace)
{
	speedY *= -1;
	y = yReplace;
}
void Ball::horizontalBounce(int xReplace)
{
	speedX *= -1;
	x = xReplace;
}
void Ball::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}