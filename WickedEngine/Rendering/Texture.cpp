#include "Texture.h"

#include "../General/Image.h"
#include <glad/gl.h>
#include <iostream>

Texture::Texture(const std::string& name, const std::string& fileName) : BaseTexture(name)
{
	TextureForm textureForm;
	ImagePtr textureImage = Image::Make(fileName);

	textureForm.mipmapLevel = 0;
	textureForm.internalFormat = textureImage->GetNChannels() == 3 ? GL_RGB : GL_RGBA;
	textureForm.width = textureImage->GetWidth();
	textureForm.height = textureImage->GetHeight();
	textureForm.border = 0;
	textureForm.texelFormat = textureForm.internalFormat;
	textureForm.texelDataFormat = GL_UNSIGNED_BYTE;
	textureForm.textureData = textureImage->GetData();
	textureForm.sWrap = GL_REPEAT;
	textureForm.tWrap = GL_REPEAT;
	textureForm.minFilter = GL_LINEAR_MIPMAP_LINEAR;
	textureForm.maxFilter = GL_LINEAR;

	Create2DTexture(textureForm);
}

Texture::Texture(const std::string& name, const ColorPtr& color) : Texture(name, *color)
{
	
}

Texture::Texture(const std::string& name, const Color& color) : BaseTexture(name)
{
	const unsigned char colorData[4] = { static_cast<unsigned char>(color.r * 255),
										 static_cast<unsigned char>(color.g * 255),
										 static_cast<unsigned char>(color.b * 255),
										 static_cast<unsigned char>(color.a * 255) };

	TextureForm textureForm;

	textureForm.mipmapLevel = 0;
	textureForm.internalFormat = GL_RGBA;
	textureForm.width = 1;
	textureForm.height = 1;
	textureForm.border = 0;
	textureForm.texelFormat = GL_RGBA;
	textureForm.texelDataFormat = GL_UNSIGNED_BYTE;
	textureForm.textureData = colorData;
	textureForm.sWrap = GL_REPEAT;
	textureForm.tWrap = GL_REPEAT;
	textureForm.minFilter = GL_NEAREST;
	textureForm.maxFilter = GL_NEAREST;

	Create2DTexture(textureForm);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, id);
	glDeleteTextures(1, &id);
}