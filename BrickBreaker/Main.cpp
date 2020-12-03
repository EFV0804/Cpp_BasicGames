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

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
bool quit = false;
bool winLose = false;
int ballCount = 5;

Paddle paddle = Paddle(300, 730, 50, 16, 10);
Ball ball = Ball(paddle.getX() + (paddle.getW() / 2) - 5, (paddle.getY() - 10), 10, 10, 0, 0);
InputState inputState = InputState();
Text ballCountText = Text(50,50,20,50);

//Array used to store brick coordinates
array <array<int, 2>, 17> brickCoordArray =
{ {
	{280,70},
	{110,120},
	{160,120},
	{210,120},
	{260,120},
	{310,120},
	{360,120},
	{410,120},
	{460,120},
	{510,120},
	{310,170},
	{360,170},
	{410,170},
	{460,170},
	{390,220},
	{440,220},
	{490,220},
} };

//Vector used to store the brick instances created using brick coordinates from array
vector<Brick*> brickVector;


void draw(SDL_Renderer* renderer);
void update(InputState* inputState, SDL_Renderer* renderer);
bool handleInput();
void close(SDL_Window* window, SDL_Renderer* renderer);
bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB);
void load(SDL_Renderer* renderer);
void unload();
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
	unload();


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
void unload()
{
	while(!brickVector.empty())
	{
		delete brickVector.back();
	}
}
void load(SDL_Renderer* renderer)
{
	ballCountText.load(renderer, "5");

	//LOAD BRICKS (not in a single line this time)

	for (int i = 0; i < brickCoordArray.size(); i++)
	{
		int x = brickCoordArray[i][0];
		int y = brickCoordArray[i][1];
		Brick* brick = new Brick(x, y);
		brickVector.push_back(brick);
	}
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
int AABBSidesCollision(SDL_Rect* rectA, SDL_Rect* rectB, Ball* ball) //Returns 0 for horizontal collision, 1 for vertical
{

	int yMinB = rectB->y;
	int yMaxB = rectB->y + rectB->h;
	int yMinA = rectA->y;
	int yMaxA = rectA->y + rectA->h;
	int xMinA = rectA->x;
	int xMaxA = rectA->x + rectA->w;
	int xMinB = rectB->x;
	int xMaxB = rectB->x + rectB->w;
	int speedXA = ball->getSpeedX();
	int speedYA = ball->getSpeedY();

	//Horizontal
	if (!(xMaxA + speedXA < xMinB || xMinA + speedXA > xMaxB || yMaxA < yMinB || yMinA > yMaxB))
	{
		return 0;
	}
	//Vertical
	if (!(xMaxA < xMinB || xMinA > xMaxB || yMaxA + speedYA < yMinB || yMinA + speedYA > yMaxB))
	{
		return 1;
	}
	return 2;
}
bool handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
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

	// DRAW BRICK VECTOR
	for (int i = 0; i < brickCoordArray.size(); i++)
	{
		if (!brickVector[i]->isDestroyed) //doesn't draw if brick is destroyed
		{
			brickVector.at(i)->draw(renderer);
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
		SDL_Rect rectBrick = brickVector.at(i)->toRect(); //create rect to check collision

		//Int to store AABBSidesCollision() return value, 0 = horizontal, 1 = vertical
		int brickCollisionDirection = AABBSidesCollision(&rectBall, &rectBrick, &ball);
		
		if (!brickVector[i]->isDestroyed) // Only check for collision if brick is not already destroyed
		{
			if (brickCollisionDirection == 0)
			{
				ball.horizontalBounce();
				brickVector[i]->isDestroyed = true;
			}
			if (brickCollisionDirection == 1)
			{
				ball.verticalBounce();
				brickVector[i]->isDestroyed = true;
			}
		}
	}

	//BALL AND PADDLE COLLISION
	if (AABBCollision(&rectBall, &rectPaddle))
	{
		ball.verticalBounce();
		ball.setY(rectPaddle.y - rectBall.h);
	}

	//BALL BOTTOM SCREEN COLLISION
	if (ball.getY() > SCREEN_HEIGHT - ball.getH()) //If ball goes out of bottom screen, the ball count is decremented and ball is reset on paddle.
	{
		ball.reset(paddle.getX()+(paddle.getW()/2) - ball.getW()/2, (paddle.getY() - ball.getH())); //Ball is reset in position and has zero speed
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
			if (brickVector[i]->isDestroyed)
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