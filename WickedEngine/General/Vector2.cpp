#include "Vector2.h"

#include <iostream>

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(double x, double y) : x(x), y(y) {}
Vector2::Vector2(double cords[2]) : x(cords[0]), y(cords[1]) {}

Vector2& Vector2::operator= (const Vector2& vec2)
{
	x = vec2.x;
	y = vec2.y;

	return *this;
}

double& Vector2::operator[] (int i)
{
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		std::cerr << "Vector2 out of bounds access" << std::endl;
		double errorValue = 0;
		return errorValue;
	}
}

Vector2::operator glm::vec2() const
{
	glm::vec2 glmVec2;

	glmVec2.x = (float)x;
	glmVec2.y = (float)y;

	return glmVec2;
}