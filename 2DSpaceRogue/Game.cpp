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
void Game::load()
{
	GeneralMap mappy = GeneralMap();
	map = mappy;
	map.generateMap();
	map.generateLocalMap();

}
void Game::update()
{
	isRunning = inputs();
}
void Game::loop()
{
	while (isRunning)
	{
		renderer.beginDraw();
		update();
		map.draw(&renderer);
		renderer.endDraw();
	}
}
void Game::unload()
{
	
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
bool Game::inputs()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		map.handleInputs(&e);
	}
	return true;
}
