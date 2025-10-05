#include "Texture.h"

#include "../General/Image.h"
#include <glad/gl.h>
#include <iostream>

Texture::Texture(const std::string& name, const std::string& fileName) : name(name), id(0)
{
	ImagePtr textureImage = Image::Make(fileName);

	const int internalFormat = textureImage->GetNChannels() == 3 ? GL_RGB : GL_RGBA;
	const int imageWidth = textureImage->GetWidth();
	const int imageHeight = textureImage->GetHeight();
	const int imageBorder = 0;
	
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, mipmapOriginalLevel, internalFormat, imageWidth, imageHeight, imageBorder,
				 internalFormat, GL_UNSIGNED_BYTE, textureImage->GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& name, const ColorPtr& color) : Texture(name, *color)
{
	
}

Texture::Texture(const std::string& name, const Color& color) : name(name), id(0)
{
	const int internalFormat = GL_RGBA;
	const int imageWidth = 1;
	const int imageHeight = 1;
	const int imageBorder = 0;
	const unsigned char colorData[4] = { static_cast<unsigned char>(color.r * 255),
										 static_cast<unsigned char>(color.g * 255),
										 static_cast<unsigned char>(color.b * 255),
										 static_cast<unsigned char>(color.a * 255) };

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, mipmapOriginalLevel, internalFormat, imageWidth, imageHeight, imageBorder,
		internalFormat, GL_UNSIGNED_BYTE, colorData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, id);
	glDeleteTextures(1, &id);
}