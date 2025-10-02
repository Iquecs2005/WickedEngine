#include "Texture.h"

#include "../General/Image.h"
#include <glad/gl.h>

Texture::Texture(const std::string& name, const std::string& fileName) : name(name)
{
	ImagePtr textureImage = Image::Make(fileName);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//TO DO
	//glTexImage2D(GL_TEXTURE_2D, );
}