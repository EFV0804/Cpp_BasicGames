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
#include<string>
#include<fstream>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using std::vector;
using std::array;
using std::string;

class Scene
{
public:
	Scene(string path);
	~Scene();
	//bool initialize();
	void load();
	void update();
	bool handleInput();
	bool AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB);
	int AABBSidesCollision(SDL_Rect* rectA, SDL_Rect* rectB, Ball* ball);
	//bool isWinLose();
	void draw();
	//void close();
	void unload();


	vector<Brick*> brickVector;
	int ballCount = 5;
	Paddle paddle;
	Ball ball;
	InputState inputState;
private:
	Text ballCountText;
	bool winLose = false;
	string path;
	vector<int> brickCoordVec;
	//array <array<int, 2>, 100> brickCoordArray =
	//{ {
	//} };
	

	Renderer renderer;
	Window window;
	/*BrickLayout brickLayout;*/
};