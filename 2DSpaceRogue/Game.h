#pragma once
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"Renderer.h"
#include"Window.h"
#include"Ship.h"
#include"GeneralMap.h"

#include<vector>

using std::vector;

class Game
{
public:

	Game() : isRunning(true)
	{}

	//static Game& instance()
	//{
	//	static Game inst;
	//	return inst;
	//}
	//Game(const Game&) = delete; //deleting copy constructor
	//Game& operator = (const Game&) = delete; //deleting assignment operator
	//Game(Game&&) = delete;
	//Game& operator = (Game&&) = delete;

	bool initialize();
	void load();
	void update();
	bool inputs();
	void loop();
	void close();
	void unload();

private:

	bool isRunning;
	Renderer renderer;
	Window window;
	GeneralMap map;
};