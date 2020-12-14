#pragma once
class InputState
{
public:
	InputState() : paddleLeft(false), paddleRight(false)
	{
	}
	bool paddleLeft;
	bool paddleRight;
	inline InputState* toInputState() const { return inputState; }

private:
	InputState* inputState = nullptr;
};