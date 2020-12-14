#pragma once
#include"InputState.h"
#include"Renderer.h"
#include"Ball.h"
#include"Text.h"
#include"Paddle.h"
#include"Brick.h"
#include"Window.h"
#include"Renderer.h"
#include<SDL.h>
#include<vector>
#include<array>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using std::vector;
using std::array;

class Scene
{
public:
	Scene();
	~Scene();
	bool initialize();
	void load();
	void update();
	bool handleInput();
	bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB); //scene
	int AABBSidesCollision(SDL_Rect* rectA, SDL_Rect* rectB, Ball* ball); //scene
	bool isWinLose();
	void draw();
	void close();

private:
	int ballCount = 5;
	Text ballCountText;
	bool winLose = false;
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
	vector<Brick*> brickVector;
	Paddle paddle;
	Ball ball;
	InputState inputState; //scene
	Renderer renderer;
	Window window;
	/*BrickLayout brickLayout;*/
};