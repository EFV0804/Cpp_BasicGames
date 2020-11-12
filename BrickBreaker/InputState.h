#pragma once
struct InputState
{
	InputState() : paddleLeft(false), paddleRight(false)
	{
	}
	bool paddleLeft;
	bool paddleRight;
};