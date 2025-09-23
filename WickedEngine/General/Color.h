#pragma once

#include "Vector4.h"

class Color
{
public:
	double& r, g, b, a;
	static const Color white;

	inline Color();
	Color(const Color& color);
	inline Color& operator= (const Color& color);

private:
	Vector4 colorComponents;
};

Color::Color() : r(colorComponents.x), g(colorComponents.y), b(colorComponents.w), a(colorComponents.w) {}

inline Color& Color::operator= (const Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;

	return *this;
}