#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<array>
#include<string>
#include<vector>

#include"Ship.h"
#include"Renderer.h"
#include"Window.h"
#include"Game.h"


using std::vector;
using std::array;
using std::string;




int main(int argc, char** argv)
{

	//LOAD
	Game game;
	bool isGameInit = game.initialize();


	//LOOP
	if (isGameInit)
	{
		game.load();
		game.loop();
	}


	return 0;
}
