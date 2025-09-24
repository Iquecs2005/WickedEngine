#pragma once

#include <glm/glm.hpp>
#include <iostream>

class Vector3
{
public:
	double x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3(double cords[3]) : x(cords[0]), y(cords[1]), z(cords[2]) {}
	//Vector3(const Vector3* vec3) : x(vec3->x), y(vec3->y), z(vec3->z) {}

	Vector3& operator= (const Vector3& vec3)
	{
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;

		return *this;
	}

	Vector3& operator+= (const Vector3& vec3);

	double& operator[] (int i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			std::cerr << "Vector3 out of bounds access" << std::endl;
			double errorValue = 0;
			return errorValue;
		}
	}

	operator glm::vec3() const 
	{
		glm::vec3 glmVec3;

		glmVec3.x = (float) x;
		glmVec3.y = (float) y;
		glmVec3.z = (float) z;

		return glmVec3;
	}

	explicit operator glm::vec4() const
	{
		glm::vec4 glmVec4;

		glmVec4.x = (float) x;
		glmVec4.y = (float) y;
		glmVec4.z = (float) z;
		glmVec4.w = 1;

		return glmVec4;
	}

	friend inline Vector3 operator* (const Vector3& vec1, const Vector3& vec2)
	{
		return Vector3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
	}

	friend inline Vector3 operator+ (const Vector3& vec1, const Vector3& vec2)
	{
		return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}


};

