#include"Brick.h"

Brick::Brick(int pX, int pY)
	:x(pX), y(pY)
{
	w = 10;
	h = 10;
}
Brick::~Brick()
{

}
SDL_Rect Brick::toRect()
{
	SDL_Rect rect = { x,y,w,h };
	return rect;
}
void Brick::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = toRect();
	SDL_RenderFillRect(renderer, &rect);
}
void Brick::update()
{

}