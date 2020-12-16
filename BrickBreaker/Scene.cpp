#include"Scene.h"

Scene::Scene(string pathP)
{
	path = pathP;
}
Scene::~Scene()
{

}
bool Scene::initialize()
{

	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	return isWindowInit && isRendererInit;
}
bool Scene::AABBCollision(SDL_Rect* rectA, SDL_Rect* rectB)
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
int Scene::AABBSidesCollision(SDL_Rect* rectA, SDL_Rect* rectB, Ball* ball) //Returns 0 for horizontal collision, 1 for vertical
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
void Scene::load()
{
	paddle = Paddle(300, 730, 250, 16, 10);
	ball = Ball(paddle.getX() + (paddle.getW() / 2) - 5, (paddle.getY() - 10), 10, 10, 0, 0);
	ballCountText = Text(50, 50, 20, 50);
	ballCountText.load(renderer.toSDLRenderer(), "5");
	
	//LOAD BRICK COORDINATES
	//1.create file stream and string unit
	string line;
	std::ifstream brickCoordData;
	brickCoordData.open(path);


			//SET VECTOR SIZE
			//2. read first line until delimiter "=", if line string is "size", read the next line, convert to int and set vector size
	getline(brickCoordData, line, '=');
	if (line == "size")
	{
		getline(brickCoordData, line, ',');
		brickCoordVec.resize(atoi(line.c_str()));
	}

			//LOAD COORDINATES INTO VECTOR
			//3.For every slot in vec, get a string up to every ",", convert to string and store in vec
	for (int i = 0; i < brickCoordVec.size(); i++)
	{
		getline(brickCoordData, line, ',');
		brickCoordVec.at(i) = atoi(line.c_str());
	}

	//LOAD BRICKS
	for (int i = 0; i < brickCoordVec.size(); i++)
	{
		int x = brickCoordVec.at(i);
		i++;
		int y = brickCoordVec.at(i);
		Brick* brick = new Brick(x, y);
		brickVector.push_back(brick);
	}
}
void Scene::update()
{
	ball.update(window.getWidth(), window.getHeight(), inputState.toInputState());
	paddle.update(inputState, window.getWidth());

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
	if (ball.getY() > window.getHeight() - ball.getH()) //If ball goes out of bottom screen, the ball count is decremented and ball is reset on paddle.
	{
		ball.reset(paddle.getX() + (paddle.getW() / 2) - ball.getW() / 2, (paddle.getY() - ball.getH())); //Ball is reset in position and has zero speed
		ballCount--;

		char newText[3]; // Buffer error if score gets to 100, change buffer size here, in text.h and text.cpp -> load()
		sprintf_s(newText, "%d", ballCount);
		ballCountText.changeText(renderer.toSDLRenderer(), newText);

		ball.isBallReset = true; //Sets bool to true in order to triger conditional in inputHandle()
	}
}
bool Scene::handleInput()
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
bool Scene::isWinLose()
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
void Scene::draw()
{
	renderer.beginDraw();
	paddle.draw(&renderer);
	ball.draw(&renderer);
	ballCountText.draw(&renderer);
	// DRAW BRICK VECTOR
	for (int i = 0; i < brickVector.size(); i++)
	{
		if (!brickVector[i]->isDestroyed) //doesn't draw if brick is destroyed
		{
			brickVector.at(i)->draw(&renderer);
		}
	}
	renderer.endDraw();
}
void Scene::close()
{
	renderer.close();
	window.close();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}