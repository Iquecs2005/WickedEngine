#pragma once

#include <glm/glm.hpp>
#include <iostream>

class Vector2
{
public:
	double x, y;

	Vector2();
	Vector2(double x, double y);
	Vector2(double cords[2]);

	Vector2& operator= (const Vector2& vec3);
	double& operator[] (int i);
	operator glm::vec2() const;

	friend inline Vector2 operator* (const Vector2& vec1, const Vector2& vec2);
	friend inline Vector2 operator+ (const Vector2& vec1, const Vector2& vec2);
};

inline Vector2 operator* (const Vector2& vec1, const Vector2& vec2)
{
	return Vector2(vec1.x * vec2.x, vec1.y * vec2.y);
}

inline Vector2 operator+ (const Vector2& vec1, const Vector2& vec2)
{
	return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
}