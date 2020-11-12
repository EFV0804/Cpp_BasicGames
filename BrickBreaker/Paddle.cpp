#include"Paddle.h"


Paddle::Paddle(int pX, int pY, int pW, int pH, int pSpeedX)
	:x(pX),y(pY),w(pW),h(pH), speedX(pSpeedX)
{

}
//Paddle::Paddle(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
//{
//	x = SCREEN_WIDTH / 2 - w / 2;
//	y = SCREEN_HEIGHT - h;
//	w = 50;
//	h = 20;
//}
Paddle::~Paddle()
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
void Paddle::moveLeft()
{
	x -= speedX;
	if (x < 0)
	{
		x = 0;
	}
}
void Paddle::moveRight(const int SCREEN_WIDTH)
{
	x += speedX;
	if (x > SCREEN_WIDTH-w)
	{
	x = SCREEN_WIDTH - w;
	}
}
void Paddle::update(InputState* inputState, const int SCREEN_WIDTH)
{
	if (inputState->paddleLeft)
	{
		moveLeft();
	}
	else if (inputState->paddleRight)
	{
		moveRight(SCREEN_WIDTH);
	}
}