#include "Color.h"

//static const Color white = Color(255, 255, 255, 255);

Color::Color(const Color& color) : r(colorComponents.x), g(colorComponents.y), b(colorComponents.w), a(colorComponents.w)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}