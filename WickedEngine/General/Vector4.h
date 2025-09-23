#pragma once

#include <glm/glm.hpp>

class Vector4
{
public:
	double x, y, z, w;

	Vector4();
	Vector4(double x, double y, double z, double w);
	Vector4(double cords[4]);

	Vector4& operator= (const Vector4& vec3);
	double& operator[] (int i);
	explicit operator glm::vec3() const;
	operator glm::vec4() const;

	friend inline Vector4 operator* (const Vector4& vec1, const Vector4& vec2);
	friend inline Vector4 operator+ (const Vector4& vec1, const Vector4& vec2);
};

inline Vector4 operator* (const Vector4& vec1, const Vector4& vec2)
{
	return Vector4(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
}

inline Vector4 operator+ (const Vector4& vec1, const Vector4& vec2)
{
	return Vector4(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w * vec2.w);
}

