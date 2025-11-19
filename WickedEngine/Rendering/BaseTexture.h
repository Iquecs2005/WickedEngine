#pragma once

#include <string>

class BaseTexture
{
public:
	inline unsigned int GetTextureId();
	inline std::string GetTextureName();
	inline unsigned int GetWidth();
	inline unsigned int GetHeight();
protected:
	unsigned int id;
	std::string name;
	unsigned int width;
	unsigned int height;

	static const int mipmapOriginalLevel = 0;

	inline BaseTexture(std::string name);
	virtual ~BaseTexture() = default;
};

inline BaseTexture::BaseTexture(std::string name) : name(name), id(0), width(0), height(0)
{

}

inline unsigned int BaseTexture::GetTextureId()
{
	return id;
}

inline std::string BaseTexture::GetTextureName()
{
	return name;
}

inline unsigned int BaseTexture::GetWidth()
{
	return width;
}

inline unsigned int BaseTexture::GetHeight()
{
	return height;
}
