#include <memory>

class Texture;
using TexturePtr = std::shared_ptr<Texture>;

#pragma once

#include <string>

class Texture
{
public:
	static inline TexturePtr Make(const std::string& name, const std::string& fileName);
protected:
	Texture(const std::string& name, const std::string& fileName);
private:
	unsigned int id;
	std::string name;
};

inline TexturePtr Texture::Make(const std::string& name, const std::string& fileName)
{
	return TexturePtr(new Texture(name, fileName));
}


