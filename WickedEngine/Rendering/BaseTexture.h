#include <memory>

class BaseTexture;
using BaseTexturePtr = std::shared_ptr<BaseTexture>;

#pragma once

#include "shader.h"
#include <string>

class BaseTexture
{
public:
	void Load(ShaderPtr shader, std::string variableName);
	void Unload(ShaderPtr shader);

	inline std::string GetTextureName() const;

	inline unsigned int GetId() const;
	inline unsigned int GetWidth() const;
	inline unsigned int GetHeight() const;

	struct TextureForm
	{
		unsigned int mipmapLevel;
		int internalFormat;
		unsigned int width;
		unsigned int height;
		unsigned int border;
		unsigned int texelFormat;
		unsigned int texelDataFormat;
		const void* textureData;

		unsigned int sWrap;
		unsigned int tWrap;
		unsigned int minFilter;
		unsigned int maxFilter;
	};
protected:
	std::string name;

	unsigned int id = 0;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int mipmapLevel = 0;
	
	inline BaseTexture(const std::string& name);
	virtual ~BaseTexture();

	unsigned int Create2DTexture(const TextureForm& textureForm, bool saveValues = true);
};

inline BaseTexture::BaseTexture(const std::string& name) : name(name)
{

}

inline std::string BaseTexture::GetTextureName() const
{
	return name;
}

inline unsigned int BaseTexture::GetId() const
{
	return id;
}

inline unsigned int BaseTexture::GetWidth() const
{
	return width;
}

inline unsigned int BaseTexture::GetHeight() const
{
	return height;
}
