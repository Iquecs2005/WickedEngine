#include <memory>

class Texture;
using TexturePtr = std::shared_ptr<Texture>;

#pragma once

#include "BaseTexture.h"
#include <string>
#include "../General/Color.h"

class Texture : public BaseTexture
{
public:
	static inline TexturePtr Make(const std::string& name, const unsigned int width, const unsigned int height);
	static inline TexturePtr Make(const std::string& name, const std::string& fileName);
	static inline TexturePtr Make(const std::string& name, const ColorPtr& color);
	static inline TexturePtr Make(const std::string& name, const Color& color);

	static inline TexturePtr GetDefaultTexture();
	static inline TexturePtr GetDefaultNormalMap();

	~Texture();
protected:
	Texture(const std::string& name, const std::string& fileName);
	Texture(const std::string& name, const Color& color);
	Texture(const std::string& name, const ColorPtr& color);
};

inline TexturePtr Texture::Make(const std::string& name, const std::string& fileName)
{
	return TexturePtr(new Texture(name, fileName));
}

inline TexturePtr Texture::Make(const std::string& name, const ColorPtr& color)
{
	return TexturePtr(new Texture(name, color));
}

inline TexturePtr Texture::Make(const std::string& name, const Color& color)
{
	return TexturePtr(new Texture(name, color));
}

inline TexturePtr Texture::GetDefaultTexture()
{
	static const TexturePtr defaultTexture = Texture::Make(std::string("DefaultTexture"), Color::white);
	return defaultTexture;
}

inline TexturePtr Texture::GetDefaultNormalMap()
{
	static const TexturePtr defaultNormalMap = Texture::Make(std::string("DefaultNormalMap"), Color::Make(0.5f, 0.5f, 1.0f));
	return defaultNormalMap;
}