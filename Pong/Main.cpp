#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<cstdio>
#include"Ball.h"
#include"Paddle.h"
#include"InputState.h"
#include"Text.h"



//DEFINITIONS
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
bool quit = false;
Ball ball = Ball(0, 100, 32, 32, 6, 6); //(x,y,w,h,speedX,speedY)
Paddle leftPaddle = Paddle(0, 200, 128, 32, 4); //(x,y,h,w,speedY)
Paddle rightPaddle = Paddle((SCREEN_WIDTH-32), 200, 128, 32, 4);
InputState inputStateLeft = InputState();
InputState inputStateRight = InputState();
Text playerScoreText = Text(120, 100, 25, 50);
Text opponentScoreText = Text(650, 100, 25, 50);
int playerScore = 99;
int opponentScore = 99;

void load(SDL_Renderer* renderer);
bool handleInput();
void update(SDL_Renderer* renderer);
void draw(SDL_Renderer*);
void close(SDL_Window*, SDL_Renderer*);
bool AABBcollision(SDL_Rect* rectA, SDL_Rect * rectB);

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
	load(renderer);
	while (!quit)
	{
		//INPUTS
		quit = handleInput();

		//UPDATE
		update(renderer);
		//DRAW
		draw(renderer);
	}

	//END
	close(window, renderer);

	return 0;

}

void load(SDL_Renderer* renderer)
{
	playerScoreText.load(renderer, "0");
	opponentScoreText.load(renderer, "0");
}
bool handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_z)
			{
				inputStateLeft.paddleUp = true;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				inputStateLeft.paddleDown = true;
			}
			if (e.key.keysym.sym == SDLK_i)
			{
				inputStateRight.paddleUp = true;
			}
			else if (e.key.keysym.sym == SDLK_j)
			{
				inputStateRight.paddleDown = true;
			}
		}
		else if (e.type == SDL_KEYUP)
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
		}
		else if (e.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}
void update(SDL_Renderer* renderer)
{
	ball.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	leftPaddle.update(&inputStateLeft, SCREEN_HEIGHT);
	rightPaddle.updateAi(SCREEN_HEIGHT, ball.y); // for player two use update()

	//COLLISIONS
	SDL_Rect ballRect = ball.toRect();
	SDL_Rect leftPaddleRect = leftPaddle.toRect();
	SDL_Rect rightPaddleRect = rightPaddle.toRect();
	if (AABBcollision(&ballRect, &leftPaddleRect))
	{
		ball.horizontalBounce(leftPaddleRect.x + leftPaddleRect.w);
	}
	else if (AABBcollision(&ballRect, &rightPaddleRect))
	{
		ball.horizontalBounce(rightPaddleRect.x - rightPaddleRect.w);
	}

	// POINTS
	if (ball.getX() > SCREEN_WIDTH - ball.getWidth())
	{
		++playerScore;
		ball.setX(SCREEN_WIDTH / 2);
		char newText[3];
		sprintf_s(newText, "%d", playerScore);
		playerScoreText.changeText(renderer, newText);
	}
	else if (ball.getX() < 0)
	{
		++opponentScore;
		ball.setX(SCREEN_WIDTH / 2);
		char newText[3];
		sprintf_s(newText, "%d", opponentScore);
		opponentScoreText.changeText(renderer, newText);
	}
}
void draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0X00, 0X00, 0X50, 0XFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0XFF, 0XFF, 0XFF, 0XFF);
	playerScoreText.draw(renderer);
	opponentScoreText.draw(renderer);
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
bool AABBcollision(SDL_Rect* rectA, SDL_Rect* rectB)
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