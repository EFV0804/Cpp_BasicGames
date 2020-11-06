#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"Ball.h"
#include"Paddle.h"


//DEFINITIONS
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
bool quit = false;
Ball ball = Ball(0, 100, 32, 32, 6, 6);
Paddle leftPaddle = Paddle(0, 200, 128, 32, 4);
Paddle rightPaddle = Paddle((SCREEN_WIDTH-32), 200, 128, 32, 4);

void load();
bool handleInput();
void update();
void draw(SDL_Renderer*);
void close(SDL_Window*, SDL_Renderer*);

int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// INIT WINDOW
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

	//LOAD
	while (!quit)
	{
		//INPUTS
		quit = handleInput();

		//UPDATE
		update();

		//DRAW
		draw(renderer);
	}

	//END
	close(window, renderer);

	return 0;

}

void load()
{

}
bool handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{

		}
		else if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void update()
{
	ball.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	/*leftPaddle.update();*/
}
void draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0X00, 0X00, 0X50, 0XFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0XFF, 0XFF, 0XFF, 0XFF);
	ball.draw(renderer);
	leftPaddle.draw(renderer);
	rightPaddle.draw(renderer);

	SDL_RenderPresent(renderer);
}
void close(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}