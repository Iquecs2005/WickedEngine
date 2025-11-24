#include "DepthTexture.h"

#include <glad/gl.h>

DepthTexture::DepthTexture(const std::string& name, unsigned int width, unsigned int height) 
	: BaseTexture(name)
{
	TextureForm textureForm;

	textureForm.mipmapLevel = 0;
	textureForm.internalFormat = GL_DEPTH_COMPONENT32F;
	textureForm.width = width;
	textureForm.height = height;
	textureForm.border = 0;
	textureForm.texelFormat = GL_DEPTH_COMPONENT;
	textureForm.texelDataFormat = GL_FLOAT;
	textureForm.textureData = 0;
	textureForm.sWrap = GL_CLAMP_TO_EDGE;
	textureForm.tWrap = GL_CLAMP_TO_EDGE;
	textureForm.minFilter = GL_LINEAR;
	textureForm.maxFilter = GL_LINEAR;

	Create2DTexture(textureForm);
	SetCompareMode();
}

void DepthTexture::SetCompareMode()
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, 0);
}