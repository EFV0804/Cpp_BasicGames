#pragma once

struct InputState
{
	InputState(): paddleUp(false), paddleDown (false)
	{
	}
	bool paddleUp;
	bool paddleDown;
};