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
SDL_Rect Ball::toRect() //Creates rectangle using values set in constructor
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Ball::draw(SDL_Renderer* renderer) //Calls toRect() to create rectangle, draw rectangle
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Ball::update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	x += speedX;
	y += speedY;

	// Makes ball bounce if it hits to or bottom of screen
	if (y<0)
	{
		verticalBounce(0);
	}
	if (y > (SCREEN_HEIGHT - h))
	{
		verticalBounce((SCREEN_HEIGHT - h));
	}
}
void Ball::horizontalBounce(int xReplace) //Used in Main -> update() in case of collision with Paddles
{
	speedX *= -1; // reverse speed
	x = xReplace; //set x 
}
void Ball::verticalBounce(int yReplace)
{
	speedY *= -1; //reverse speed
	y = yReplace; //set y to yReplace (screen edge position)
}
void Ball::setX(int newX)
{
	x = newX;
}
int Ball::getX() const
{
	return x;
}
int Ball::getWidth() const
{
	return w;
}