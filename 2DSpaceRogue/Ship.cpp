#include"Ship.h"
Ship::Ship()
{
	x = 100;
	y = 100;
	w = 10;
	h = 10;
}
Ship::Ship(int pX, int pY, int pW, int pH)
{
	x = pX;
	y = pY;
	w = pW;
	h = pH;
}
SDL_Rect Ship::toRect()
{
	SDL_Rect rect{ x, y, w, h };
	return rect;
}
void Ship::draw(Renderer* renderer)
{
	SDL_Rect rect = toRect();
	renderer->drawRect(rect, 238, 136, 164, 255);
}
void Ship::update()
{
	
}
void Ship::setPos(int xP, int yP)
{
	x = xP;
	y = yP;
}