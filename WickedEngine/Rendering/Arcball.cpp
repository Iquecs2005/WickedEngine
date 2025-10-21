#include "Arcball.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const double PI = 3.14159265359;

Arcball::Arcball(float distance) : distance(distance), x0(0), y0(0)
{
	for (int i = 0; i < 16; i++)
	{
		matrix[i] = i % 5 == 0 ? 1.0f : 0.0f;
	}
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

	float ax = uy * vz - uz * vy;
	float ay = uz * vx - ux * vz;
	float az = ux * vy - uy * vx;

	float theta = 2 * (float)asin(sqrt(ax * ax + ay * ay + az * az));

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -distance);
	glRotatef(theta * 180.0f / PI, ax, ay, az);
	glTranslatef(0.0f, 0.0f, distance);
	glMultMatrixf(matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
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

const float* Arcball::GetMatrix() const
{
	return matrix;
}