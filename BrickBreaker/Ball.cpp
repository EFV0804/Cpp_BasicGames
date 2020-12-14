#include "Ball.h"
#include"Paddle.h"
#include<cstdio> 

Ball::Ball()
{}
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
void Ball::reset(const int pX, const int pY)
{
	x = pX;
	y = pY;
	speedX = 0;
	speedY = 0;
}
void Ball::dirSet(InputState* inputState)
{
	if (inputState->paddleLeft)  //setting speed direction depending on player input works
	{
		speedX = -6;
		speedY = 6;
	}
	else if (inputState->paddleRight)
	{
		speedX = 6;
		speedY = 6;
	}
}
void Ball::update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, InputState* inputState)
{
	x += speedX;
	y += speedY;

	//LEFT SCREEN EDGE BOUNCE
	if (x < 0)
	{
		horizontalBounce();
	}
	//RIGHT SCREEN EDGE BOUNCE
	if (x > SCREEN_WIDTH - w)
	{
		horizontalBounce();
	}
	//TOP SCREEN EDGE BOUNCE
	if (y < 0)
	{
		verticalBounce();
	}

	//FOR BOTTOM SCREEN EDGE SEE --> scene -> update()
}
void Ball::draw(Renderer* renderer)
{
	SDL_Rect rect = toRect();
	renderer->drawRect(rect);
}
void Ball::horizontalBounce()
{
	speedX *= -1;
}
void Ball::verticalBounce()
{
	speedY *= -1;
}
