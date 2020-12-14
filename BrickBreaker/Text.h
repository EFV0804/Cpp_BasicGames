#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include"Renderer.h"

class Text
{
public:
	Text(int pX, int pY, int pW, int pH);
	Text();
	~Text();
	void load(SDL_Renderer* renderer, const char newText[3]);
	void changeText(SDL_Renderer* renderer, const char* newText);
	void draw(Renderer* renderer);
	SDL_Texture* getTex() { return texture; }
	SDL_Rect toRect();
private:
	int x;
	int y;
	int w;
	int h;
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Texture* texture;
};
