#include <memory>

class CustomTexture;
using CustomTexturePtr = std::shared_ptr<CustomTexture>;

#pragma once

#include <string>

#include "BaseTexture.h"

class CustomTexture : public BaseTexture
{
public:
	static inline CustomTexturePtr Make(const std::string& name, const TextureForm& form);
protected:
	CustomTexture(const std::string& name, const TextureForm& form);
};

inline CustomTexturePtr CustomTexture::Make(const std::string& name, const TextureForm& form)
{
	return CustomTexturePtr(new CustomTexture(name, form));
}