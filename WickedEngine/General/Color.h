#pragma once

#include "Vector4.h"

class Color
{
public:
	double& r, g, b, a;

	inline Color();
	Color(const Color& color);

	static const Color white;
private:
	Vector4 colorComponents;
};

Color::Color() : r(colorComponents.x), g(colorComponents.y), b(colorComponents.w), a(colorComponents.w) {}