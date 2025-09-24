#include "Vector3.h"

Vector3& Vector3::operator+= (const Vector3& vec3)
{
	this->x += vec3.x;
	this->y += vec3.y;
	this->z += vec3.z;

	return *this;
}