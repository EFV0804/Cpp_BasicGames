#pragma once
#include<vector>
#include<string>
#include"Scene.h"

using std::vector;
using std::string;

class Game
{
public:

	Game() : isRunning(true),
		sceneNum(0),
		currentScene(nullptr)
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
	void initializeScenes();
	void loadScene();
	void changeScene();
	void update();
	void loop();
	bool isWin();
	bool isLose();
	void close();
	void unload();

private:

	bool isRunning;
	vector<string> filenamesVec{"scene00.txt", "scene01.txt", "scene02.txt"};
	vector<Scene*> scenes;
	int sceneNum;
	Scene* currentScene;
	string path = "D:\\ARTFX\\3D3 - Prog\\BLAISE_CAZALET_G\\C++\\Exercice\\";
	Renderer renderer;
	Window window;
};