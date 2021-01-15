#include"Game.h"
bool Game::initialize()
{
	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	return isWindowInit && isRendererInit;
}
void Game::initializeScenes()
{
	scenes.resize(filenamesVec.size());
	//Loop over every name in vec to create a scene and add it to scenes vector
	for (int i = 0; i < filenamesVec.size(); i++)
	{
		Scene* scene = new Scene(path + filenamesVec.at(i));
		scenes.push_back(scene);
	}
}

void Game::loadScene()
{
	initializeScenes();
	//scene index
	sceneNum = 0;
	//current scene is the scene at the current index in scenes vector (index is incremented when level is won)
	currentScene = scenes.at(sceneNum);
	currentScene->load();
}
void Game::update()
{
	currentScene->update();
	bool victory = isWin();
	bool defeat = isLose();
	if (victory)
	{
		//currentScene->unload();
		sceneNum++;
		changeScene();
		currentScene->load();
	}
	if (defeat)
	{
		//close();
	}

}
void Game::changeScene()
{
	currentScene = scenes.at(sceneNum);
}
void Game::loop()
{
	while (isRunning)
	{
		currentScene->handleInput();
		update();
		currentScene->draw();
	}
}
bool Game::isWin()
{
	int destroyedBricks = 0;

	for (int i = 0; i < currentScene->brickVector.size(); i++)
	{
		if (currentScene->brickVector[i]->isDestroyed)
		{
			destroyedBricks++;
		}
	}
	if (destroyedBricks == currentScene->brickVector.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Game::isLose()
{
	if (currentScene->ballCount == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Game::unload()
{
	currentScene->unload();

	for (auto s : scenes)
	{
		delete s;
	}

}
void Game::close()
{
	renderer.close();
	window.close();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}