#include "CustomTexture.h"

CustomTexture::CustomTexture(const std::string& name, const TextureForm& form)
	: BaseTexture(name)
{
	Create2DTexture(form);
}