#include "Arcball.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <iostream>

const float PI = 3.14159265359;

Arcball::Arcball(float distance) : distance(distance), x0(0), y0(0), matrix(1)
{
	
}

void Arcball::InitMouseMotion(float x0, float y0)
{
	this->x0 = x0;
	this->y0 = y0;
}

void Arcball::AccumulateMouseMotion(float x, float y)
{
	int vp[4];

	glGetIntegerv(GL_VIEWPORT, vp);

	float ux, uy, uz;
	float vx, vy, vz;

	Map(vp[2], vp[3], x0, y0, ux, uy, uz);
	Map(vp[2], vp[3], x, y, vx, vy, vz);

	x0 = x;
	y0 = y;

	float ax = uy * vz - uz * vy;
	float ay = uz * vx - ux * vz;
	float az = ux * vy - uy * vx;

	float theta = 2 * (float)asin(sqrt(ax * ax + ay * ay + az * az));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -distance));
	model = glm::rotate(model, theta, glm::vec3(ax, ay, az));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, distance));
	matrix = model * matrix;
}

void Arcball::Map(int width, int height, float x, float y, float& px, float& py, float& pz)
{
	float r = width < height ? width / 2.0f : height / 2.0f;
	
	float X = (x - width / 2.0f) / r;
	float Y = (y - height / 2.0f) / r;
	float Z;

	float l = sqrt(X * X + Y * Y);
	if (l <= 1.0f)
	{
		Z = sqrt(1.0f - l*l);
	}
	else
	{
		X /= l;
		Y /= l;
		Z = 0.0f;
	}

	px = X;
	py = Y;
	pz = Z;
}

const glm::mat4& Arcball::GetMatrix() const
{
	return matrix;
}