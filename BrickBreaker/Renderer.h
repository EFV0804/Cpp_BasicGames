#pragma once
#include<SDL.h>

#include"Window.h"

class Renderer
{
public:
	Renderer();
	bool initialize(Window& window);
	void beginDraw();
	void drawRect(SDL_Rect& rect);
	void endDraw();
	void close();
	//void drawBall(Ball* ball);
	//void drawBrick(Brick* brick);
	//void drawPaddle(Paddle* paddle);
	//void drawText(Text* text);
	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
private:
	SDL_Renderer* SDLRenderer = nullptr;
};