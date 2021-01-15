#include"Renderer.h"

Renderer::Renderer() : SDLRenderer(nullptr)
{

}
bool Renderer::initialize(Window& window)
{
	SDLRenderer = SDL_CreateRenderer(window.toSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return true;
}
void Renderer::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 89, 89, 89, 255);
	SDL_RenderClear(SDLRenderer);
}
void Renderer::drawRect(SDL_Rect& rect, int R, int G, int B, int A)
{
	SDL_SetRenderDrawColor(SDLRenderer, R, G, B, A);
	SDL_RenderFillRect(SDLRenderer, &rect);
}
void Renderer::drawRectOutline(SDL_Rect& rect, int R, int G, int B, int A)
{
	SDL_SetRenderDrawColor(SDLRenderer, R, G, B, A);
	SDL_RenderDrawRect(SDLRenderer, &rect);
}
void Renderer::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}
void Renderer::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}