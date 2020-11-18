#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include"Ball.h"
#include"Paddle.h"
#include"Text.h"
#include"Brick.h"
#include<array>
#include<string>
#include<cstdio>
#include<vector>

using std::vector;
using std::array;
using std::string;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
bool quit = false;
bool winLose = false;
int ballCount = 5;

Ball ball = Ball(0, 100, 16, 16, 6, 6);
Paddle paddle = Paddle(350, 350, 64, 16, 10);
InputState inputState = InputState();
Text ballCountText = Text(50,50,20,50);

array <array<int, 2>, 6> brickCoordArray =
{ {
	{50,20},
	{100,20},
	{150,20},
	{200,20},
	{250,20},
	{300,20}
} };
vector<Brick> brickVector;


void draw(SDL_Renderer* renderer);
void update(InputState* inputState, SDL_Renderer* renderer);
bool handleInput();
void close(SDL_Window* window, SDL_Renderer* renderer);
bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB);
void load(SDL_Renderer* renderer);
bool isWinLose();


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
	load(renderer);
	for (int i = 0; i < 6; i++)
	{
		int x = brickCoordArray[i][0];
		int y = brickCoordArray[i][1];
		Brick brick = Brick(x, y);
		/*Brick* pBrick = &brick;*/
		brickVector.push_back(brick);
		/*brickVector.push_back(new Brick(brickCoordArray[i][0], brickCoordArray[i][1]));*/
	}
	//GAMELOOP
	while (!quit && !winLose)
	{
		quit = handleInput();
		update(&inputState, renderer);
		winLose = isWinLose();
		draw(renderer);
	}
	close(window, renderer);
	return 0;
}
void load(SDL_Renderer* renderer)
{
	ballCountText.load(renderer, "5");
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
	ballCountText.draw(renderer);
	for (int i = 0; i < 6; i++)
	{
		if (!brickVector[i].isDestroyed)
		{
			brickVector.at(i).draw(renderer);
		}
	}
	ball.draw(renderer);
	paddle.draw(renderer);
	SDL_RenderPresent(renderer);
}
void update(InputState* inputState, SDL_Renderer* renderer)
{
	ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, inputState);
	paddle.update(inputState, SCREEN_WIDTH);

	SDL_Rect rectBall = ball.toRect();
	SDL_Rect rectPaddle = paddle.toRect();

	//BALL AND BRICK COLLISION
	for (int i = 0; i < brickVector.size(); i++)
	{
		SDL_Rect rectBrick = brickVector.at(i).toRect(); //create rect to check collision
		if (AABBCollision(&rectBall, &rectBrick))
		{
			if (!brickVector[i].isDestroyed) // Only check for collision if brick is not already destroyed
			{
				ball.verticalBounce(rectBrick.y + rectBrick.h);
				brickVector[i].isDestroyed = true; //change bool when collision
			}
		}
	}


	//BALL AND PADDLE COLLISION
	if (AABBCollision(&rectBall, &rectPaddle))
	{
		ball.verticalBounce(rectPaddle.y-rectBall.h);
	}
	if (ball.y > SCREEN_HEIGHT - ball.h) //If ball goes out of bottom screen, the ball count is decremented and ball is reset on paddle.
	{
		ball.reset(paddle.getX()+(paddle.getW()/2) - ball.w/2, paddle.getY()); //Ball is reset in position and has zero speed
		ballCount--;
		char newText[3]; // Buffer error if score gets to 100, change buffer size here, in text.h and text.cpp -> load()
		sprintf_s(newText, "%d", ballCount);
		ballCountText.changeText(renderer, newText);
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
bool isWinLose()
{
	int destroyedBricks = 0;

	if (ballCount == -1)
	{
		return true;
	}
	else if (ballCount != -1)
	{
		for (int i = 0; i < brickVector.size(); i++)
		{
			if (brickVector[i].isDestroyed)
			{
				destroyedBricks++;
			}
		}
		if (destroyedBricks == brickVector.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}