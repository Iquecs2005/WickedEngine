#include <memory>

class Texture;
using TexturePtr = std::shared_ptr<Texture>;

#pragma once

#include <string>
#include "../General/Color.h"

class Texture
{
public:
	static inline TexturePtr Make(const std::string& name, const std::string& fileName);
	static inline TexturePtr Make(const std::string& name, const ColorPtr& color);
	static inline TexturePtr Make(const std::string& name, const Color& color);

	static inline TexturePtr GetDefaultTexture();
	inline unsigned int GetTextureId();
	inline std::string GetTextureName();

	~Texture();
protected:
	Texture(const std::string& name, const std::string& fileName);
	Texture(const std::string& name, const Color& color);
	Texture(const std::string& name, const ColorPtr& color);
private:
	unsigned int id;
	std::string name;

	static const int mipmapOriginalLevel = 0;
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

inline unsigned int Texture::GetTextureId()
{
	return id;
}

inline std::string Texture::GetTextureName()
{
	return name;
}
