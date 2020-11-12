#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include"Ball.h"
#include"Paddle.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
bool quit = false;

Ball ball = Ball(0, 100, 32, 32, 6, 6);
Paddle paddle = Paddle(350, 380, 100, 20, 6);

void draw(SDL_Renderer* renderer);
void update();
bool handleInput();
void close(SDL_Window* window, SDL_Renderer* renderer);
bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB);
int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("BrickBreaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//LOAD
	while (!quit)
	{
		quit = handleInput();
		update();
		draw(renderer);
	}
	close(window, renderer);
	return 0;
}
bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB)
{
	int xMinA = rectA->x;
	int xMaxA = rectA->x + rectA->w;
	int yMinA = rectA->y;
	int yMaxA = rectA->y + rectA->h;
	int xMinB = rectB->x;
	int xMaxB = rectB->x + rectB->w;
	int yMinB = rectB->y;
	int yMaxB = rectB->y + rectB->h;
	return !(xMinA > xMaxB || xMaxA < xMinB || yMinA > yMaxB || yMaxA < yMinB);
}
bool handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			//// Player 1 inputs
			//if (e.key.keysym.sym == SDLK_z)
			//{
			//	inputStateLeft.paddleUp = true;
			//}
			//else if (e.key.keysym.sym == SDLK_s)
			//{
			//	inputStateLeft.paddleDown = true;
			//}
			////Player 2 inputs (needs Paddle::update() in main update() to work)
			//if (e.key.keysym.sym == SDLK_i)
			//{
			//	inputStateRight.paddleUp = true;
			//}
			//else if (e.key.keysym.sym == SDLK_j)
			//{
			//	inputStateRight.paddleDown = true;
			//}
		}
		/*else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_z)
			{
				inputStateLeft.paddleUp = false;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				inputStateLeft.paddleDown = false;
			}
			if (e.key.keysym.sym == SDLK_i)
			{
				inputStateRight.paddleUp = false;
			}
			else if (e.key.keysym.sym == SDLK_j)
			{
				inputStateRight.paddleDown = false;
			}
		}*/
		else if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0X00, 0X00, 0X50, 0XFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0XFF, 0XFF, 0XFF, 0XFF);
	ball.draw(renderer);
	paddle.draw(renderer);
	SDL_RenderPresent(renderer);
}
void update()
{
	ball.update(SCREEN_WIDTH, SCREEN_HEIGHT);

}
void close(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}