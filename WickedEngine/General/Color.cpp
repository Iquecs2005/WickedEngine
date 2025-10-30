#include "Color.h"

#include <iostream>

const ColorPtr Color::white = Color::Make();
const ColorPtr Color::black = Color::Make(0, 0, 0);
const ColorPtr Color::red = Color::Make(0.8f, 0.1f, 0.1f);
const ColorPtr Color::green = Color::Make(0.2f, 0.8f, 0.2f);
const ColorPtr Color::blue = Color::Make(0.0f, 0.0f, 1.0f);
const ColorPtr Color::yellow = Color::Make(0.8f, 0.8f, 0.2f);

Color& Color::operator= (const Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;

	return *this;
}

Color Color::operator+ (const Color& color) const
{
	Color newColor;

	newColor.r = std::min(r + color.r, 1.0f);
	newColor.g = std::min(g + color.g, 1.0f);
	newColor.b = std::min(b + color.b, 1.0f);
	newColor.a = std::min(a + color.a, 1.0f);

	return newColor;
}

Color Color::operator* (const Color& color) const
{
	Color newColor;

	newColor.r = std::min(r * color.r, 1.0f);
	newColor.g = std::min(g * color.g, 1.0f);
	newColor.b = std::min(b * color.b, 1.0f);
	newColor.a = std::min(a * color.a, 1.0f);

	return newColor;
}

Color Color::operator* (float i) const
{
	Color newColor;

	newColor.r = std::min(r * i, 1.0f);
	newColor.g = std::min(g * i, 1.0f);
	newColor.b = std::min(b * i, 1.0f);
	newColor.a = std::min(a * i, 1.0f);

	return newColor;
}

float& Color::operator[] (int i)
{
	switch (i)
	{
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	case 3:
		return a;
	default:
		std::cerr << "Color out of bounds access" << std::endl;
		return a;
	}
}

Color::operator glm::vec3() const
{
	glm::vec3 glmVec3;

	glmVec3.x = r;
	glmVec3.y = g;
	glmVec3.z = b;

	return glmVec3;
}

Color::operator glm::vec4() const
{
	glm::vec4 glmVec4;

	glmVec4.x = r;
	glmVec4.y = g;
	glmVec4.z = b;
	glmVec4.w = a;

	return glmVec4;
}

std::ostream& operator<<(std::ostream& out, const Color& color)
{
	out << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
	return out;
}

void Color::ClampValues()
{
	r = std::min(r, 1.0f);
	r = std::max(r, 0.0f);

	g = std::min(g, 1.0f);
	g = std::max(g, 0.0f);

	b = std::min(b, 1.0f);
	b = std::max(b, 0.0f);

	a = std::min(a, 1.0f);
	a = std::max(a, 0.0f);
}

//Color::Color(const Color& color) : r(colorComponents.x), g(colorComponents.y), b(colorComponents.w), a(colorComponents.w)
//{
//	r = color.r;
//	g = color.g;
//	b = color.b;
//	a = color.a;
//}