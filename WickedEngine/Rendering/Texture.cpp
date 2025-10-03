#include "Texture.h"

#include "../General/Image.h"
#include <glad/gl.h>

Texture::Texture(const std::string& name, const std::string& fileName) : name(name)
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

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, id);
	glDeleteTextures(1, &id);
}