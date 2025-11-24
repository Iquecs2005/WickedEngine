#include "BaseTexture.h"

#include <glad/gl.h>

void BaseTexture::Load(ShaderPtr shader, std::string variableName)
{
	shader->ActiveTexture(variableName);
	glBindTexture(GL_TEXTURE_2D, id);
}

void BaseTexture::Unload(ShaderPtr shader)
{
	shader->DeactiveTexture();
}

unsigned int BaseTexture::Create2DTexture(const TextureForm& textureForm, bool saveValues)
{
	unsigned int textureId;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, textureForm.mipmapLevel, textureForm.internalFormat, 
				 textureForm.width, textureForm.height, textureForm.border,
				 textureForm.texelFormat, textureForm.texelDataFormat, textureForm.textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureForm.sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureForm.tWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureForm.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureForm.maxFilter);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (saveValues)
	{
		id = textureId;
		width = textureForm.width;
		height = textureForm.height;
		mipmapLevel = textureForm.mipmapLevel;
	}

	return textureId;
}