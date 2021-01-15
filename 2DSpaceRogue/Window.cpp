#include "Window.h"

Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT)
{

}
bool Window::initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDLWindow = SDL_CreateWindow("2DSpaceRogue", 100, 100, width, height, 0);
	return true;
}
void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}