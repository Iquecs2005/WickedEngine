#include <memory>

class Color32;
using Color32Ptr = std::shared_ptr<Color32>;

#pragma once

#include <glm/glm.hpp>
#include "Color.h"

class Color32
{
public:
	unsigned char r, g, b, a;

	static const Color32 white;
	static const Color32 black;

	inline static Color32Ptr Make();
	inline static Color32Ptr Make(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	Color32& operator= (const Color32& color);
	Color32& operator+ (const Color32& color);
	Color32& operator* (float i);
	unsigned char& operator[] (int i);
	operator glm::vec3() const;
	operator glm::vec4() const;
	operator Color() const;

private:
	inline Color32();
	inline Color32(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
};

inline Color32::Color32() 
{

}

inline Color32::Color32(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) :
	r(r), g(g), b(b), a(a) 
{

}

inline Color32Ptr Color32::Make()
{
	return Color32Ptr(new Color32());
}

inline Color32Ptr Color32::Make(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
{
	return Color32Ptr(new Color32(r, g, b, a));
}