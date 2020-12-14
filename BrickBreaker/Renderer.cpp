#include"Renderer.h"

Renderer::Renderer(): SDLRenderer(nullptr)
{

}
bool Renderer::initialize(Window& window)
{
	SDLRenderer = SDL_CreateRenderer(window.toSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return true;
}
void Renderer::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(SDLRenderer);
}
void Renderer::drawRect(SDL_Rect &rect)
{
	SDL_SetRenderDrawColor(SDLRenderer, 0XFF, 0XFF, 0XFF, 0XFF);
	SDL_RenderFillRect(SDLRenderer, &rect);
}
void Renderer::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}
void Renderer::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}
//void Renderer::drawBrick(Brick* brick)
//{
//	SDL_SetRenderDrawColor(SDLRenderer, 0XFF, 0XFF, 0XFF, 0XFF);
//	SDL_Rect rect = brick->toRect();
//	SDL_RenderFillRect(SDLRenderer, &rect);
//}
//void Renderer::drawBall(Ball* ball)
//{
//	SDL_SetRenderDrawColor(SDLRenderer, 0XFF, 0XFF, 0XFF, 0XFF);
//	SDL_Rect rect = ball->toRect();
//	SDL_RenderFillRect(SDLRenderer, &rect);
//}
//void Renderer::drawPaddle(Paddle* paddle)
//{
//	SDL_SetRenderDrawColor(SDLRenderer, 0XFF, 0XFF, 0XFF, 0XFF);
//	SDL_Rect rect = paddle->toRect();
//	SDL_RenderFillRect(SDLRenderer, &rect);
//}
//void Renderer::drawText(Text* text)
//{
//	SDL_SetRenderDrawColor(SDLRenderer, 0XFF, 0XFF, 0XFF, 0XFF);
//	SDL_Rect rect = text->toRect();
//	SDL_RenderCopy(SDLRenderer, text->getTex(), nullptr, &rect);
//}