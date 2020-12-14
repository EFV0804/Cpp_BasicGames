#include"Paddle.h"

Paddle::Paddle()
{}
Paddle::Paddle(int pX, int pY, int pW, int pH, int pSpeedX)
	:x(pX),y(pY),w(pW),h(pH), speedX(pSpeedX)
{

}
Paddle::~Paddle()
{

}
SDL_Rect Paddle::toRect()
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Paddle::draw(Renderer* renderer) //in renderer
{
	SDL_Rect rect = toRect();
	renderer->drawRect(rect);
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
void Paddle::update(InputState& inputState, const int SCREEN_WIDTH) //include in scene->udate()
{
	if (inputState.paddleLeft)
	{
		moveLeft();
	}
	else if (inputState.paddleRight)
	{
		moveRight(SCREEN_WIDTH);
	}
}