#include <memory>

class Color;
using ColorPtr = std::shared_ptr<Color>;

#pragma once

#include <glm/glm.hpp>
#include "Color.h"

class Color
{
public:
	float r, g, b, a;

	static const ColorPtr white;
	static const ColorPtr black;
	static const ColorPtr red;
	static const ColorPtr green;
	static const ColorPtr blue;
	static const ColorPtr yellow;

	inline static ColorPtr Make();
	inline static ColorPtr Make(float r, float g, float b, float a = 1);
	inline static ColorPtr Make(int r, int g, int b, int a = 255);

	inline void SetColor(float r, float g, float b, float a = 1);
	inline void SetColor(int r, int g, int b, int a = 255);

	Color& operator= (const Color& color);
	Color operator+ (const Color& color) const;
	Color operator* (const Color& color) const;
	Color operator* (float i) const;
	float& operator[] (int i);
	explicit operator glm::vec3() const;
	operator glm::vec4() const;
	
	friend std::ostream& operator<<(std::ostream& out, const Color& color);

private:
	inline Color();
	inline Color(float r, float g, float b, float a = 1);
	//inline Color(double r, double g, double b, double a = 1);
	inline Color(int r, int g, int b, int a = 255);

	void ClampValues();
};

inline Color::Color() :
	r(1), g(1), b(1), a(1)
{

}

inline Color::Color(float r, float g, float b, float a) :
	r(r), g(g), b(b), a(a)
{
	ClampValues();
}

//inline Color::Color(double r, double g, double b, double a) :
//	r((float)r), g((float)g), b((float)b), a((float)a)
//{
//	ClampValues();
//}

inline Color::Color(int r, int g, int b, int a) :
	r(r / (float)255), g(g / (float)255), b(b / (float)255), a(a / (float)255)
{
	ClampValues();
}

inline ColorPtr Color::Make()
{
	return ColorPtr(new Color());
}

inline ColorPtr Color::Make(float r, float g, float b, float a)
{
	return ColorPtr(new Color(r, g, b, a));
}

inline ColorPtr Color::Make(int r, int g, int b, int a)
{
	return ColorPtr(new Color(r, g, b, a));
}

inline void Color::SetColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;

	ClampValues();
}

inline void Color::SetColor(int r, int g, int b, int a)
{
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a / 255.0f;

	ClampValues();
}