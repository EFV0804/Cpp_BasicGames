#include"Text.h"


Text::Text(int pX, int pY, int pW, int pH)
	: x(pX), y(pY), w(pW), h(pH), font(nullptr), color({ 0XFF, 0xFF, 0XFF }),
	surface(nullptr), texture(nullptr)
{}
Text::Text() //Default constructor
	: x(120), y(100), w(25), h(50), font(nullptr), color({ 0XFF, 0xFF, 0XFF }),
	surface(nullptr), texture(nullptr)
{
}
Text::~Text() //Deconstructor
{

}
void Text::load(SDL_Renderer* renderer, const char newText[3]) //Loads the ttf file and sets it to a variable
{
	font = TTF_OpenFont("D:/ARTFX/3D3-Prog/BLAISE_CAZALET_G/C++/Exercice/cpp_BasicGames/Pong/OpenSans-Regular.ttf", 28);
	changeText(renderer, newText);
}
void Text::changeText(SDL_Renderer* renderer, const char* newText)
{
	if (texture) //Destroy any preexisting texture
	{
		SDL_DestroyTexture(texture);
	}
	surface = TTF_RenderText_Solid(font, newText, color); //Creates a surface based on loaded font, text, and color
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}
void Text::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}