#include"Brick.h"

Brick::Brick(int pX, int pY)
	:x(pX), y(pY)
{
	w = 40;
	h = 40;
	isDestroyed = false;
}
Brick::~Brick()
{
	
}
SDL_Rect Brick::toRect()
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Brick::draw(Renderer* renderer)
{
	SDL_Rect rect = toRect();
	renderer->drawRect(rect);
}
//void Brick::update()
//{
//
//}