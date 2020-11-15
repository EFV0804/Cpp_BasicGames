#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include"Ball.h"
#include"Paddle.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
bool quit = false;

Ball ball = Ball(0, 100, 16, 16, 6, 6);
Paddle paddle = Paddle(350, 350, 64, 16, 6);
InputState inputState = InputState();

void draw(SDL_Renderer* renderer);
void update(InputState* inputState);
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
		update(&inputState);
		draw(renderer);
	}
	close(window, renderer);
	return 0;
}
bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB)
{
	int yMinB = rectB->y;
	int yMaxB = rectB->y + rectB->h;
	int yMinA = rectA->y;
	int yMaxA = rectA->y + rectA->h;
	int xMinA = rectA->x;
	int xMaxA = rectA->x + rectA->w;
	int xMinB = rectB->x;
	int xMaxB = rectB->x + rectB->w;
	return !(xMinA > xMaxB || xMaxA < xMinB || yMinA > yMaxB || yMaxA < yMinB);
}
bool handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			// Player 1 inputs
			if (e.key.keysym.sym == SDLK_q)
			{
				inputState.paddleLeft = true;
				if (ball.isBallReset) // if bool has been set to true in Ball::update()
				{
					ball.dirSet(&inputState); //sets ball speed to paddle direction
					ball.isBallReset = false;
				}
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				inputState.paddleRight = true;
				if (ball.isBallReset) // if bool has been set to true in Ball::update()
				{
					ball.dirSet(&inputState); //sets ball speed to paddle direction
					ball.isBallReset = false;
				}
			}
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
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_q)
			{
				inputState.paddleLeft = false;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				inputState.paddleRight = false;
			}
			//if (e.key.keysym.sym == SDLK_i)
			//{
			//	inputStateRight.paddleUp = false;
			//}
			//else if (e.key.keysym.sym == SDLK_j)
			//{
			//	inputStateRight.paddleDown = false;
			//}
		}
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
void update(InputState* inputState)
{
	ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, inputState);
	paddle.update(inputState, SCREEN_WIDTH);

	SDL_Rect rectBall = ball.toRect();
	SDL_Rect rectPaddle = paddle.toRect();

	if (AABBCollision(&rectBall, &rectPaddle))
	{
		ball.verticalBounce(rectPaddle.y-rectBall.h);
	}
	if (ball.y > SCREEN_HEIGHT - ball.h)
	{
		ball.reset(paddle.getX()+(paddle.getW()/2) - ball.w/2, paddle.getY()); //Ball is reset in position and has zero speed
		ball.isBallReset = true; //Sets bool to true in order to triger conditional in inputHandle()
	}
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