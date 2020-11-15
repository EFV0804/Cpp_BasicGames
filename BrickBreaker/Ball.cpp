#include "Ball.h"
#include"Paddle.h"

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
void Ball::speedSet(int speedYRep, int speedXRep)
{
	speedY = speedYRep;
	speedX = speedXRep;
}
void Ball::reset(const int pX, const int pY)
{
	x = pX;
	y = pY;
	speedSet(0, 0);
}
void Ball::dirSet(InputState* inputState)
{
	if (inputState->paddleLeft)  //setting speed direction depending on player input works
	{
		speedSet(-6, -6);
	}
	else if (inputState->paddleRight)
	{
		speedSet(-6, 6);
	}
}
void Ball::update(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, InputState* inputState)
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
		reset(350, 50); //Ball is reset in position and has zero speed
		isBallReset = true; //Sets bool to true in order to triger conditional in inputHandle()
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