#include "Vector2.h"
#include<cmath>


void Vector2::set(float xP, float yP)
{
	x = xP;
	y = yP;
}
float Vector2::lengthSq() const
{
	return x * x + y * y;
}
float Vector2::length() const
{
	return sqrtf(lengthSq());
}
void Vector2::normalize()
{
	float len = length();
	x /= len;
	y /= len;
}