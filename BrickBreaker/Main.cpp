#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include"Scene.h"
#include<array>
#include<string>
#include<cstdio>
#include<vector>




using std::vector;
using std::array;
using std::string;


bool quit = false; //game instance?
bool winLose = false;

void close(); //renderer & window

//void unload(); //scene


int main(int argc, char** argv)
{
	Scene scene = Scene("D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\C++\\Exercice\\cock_Coord.txt");

	//LOAD
	scene.initialize();
	scene.load();


	//GAMELOOP
	while (!quit && !winLose)
	{
		quit = scene.handleInput();
		winLose = scene.isWinLose();
		scene.update();
		scene.draw();
	}
	/*unload();*/
	scene.close();

	return 0;
}
//void unload()
//{
//	for (auto b : brickVector)
//	{
//		delete b;
//	}
//}