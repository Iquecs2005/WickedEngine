#include "Vector4.h"

#include <iostream>

Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
Vector4::Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
Vector4::Vector4(double cords[4]) : x(cords[0]), y(cords[1]), z(cords[2]), w(cords[3]) {}

Vector4& Vector4::operator= (const Vector4& vec4)
{
	x = vec4.x;
	y = vec4.y;
	z = vec4.z;
	w = vec4.w;

	return *this;
}

double& Vector4::operator[] (int i)
{
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		std::cerr << "Vector3 out of bounds access" << std::endl;
		double errorValue = 0;
		return errorValue;
	}
}

Vector4::operator glm::vec3() const
{
	glm::vec3 glmVec3;

	glmVec3.x = (float)x;
	glmVec3.y = (float)y;
	glmVec3.z = (float)z;

	return glmVec3;
}

Vector4::operator glm::vec4() const
{
	glm::vec4 glmVec4;

	glmVec4.x = (float)x;
	glmVec4.y = (float)y;
	glmVec4.z = (float)z;
	glmVec4.w = (float)w;

	return glmVec4;
}