#include "GBuffer.h"

#include <glad/gl.h>
#include <iostream>

#include "../error.h"

GBuffer::GBuffer(int width, int height)
	: FrameBuffer(width, height)
{
	DepthTexturePtr depthTex = DepthTexture::Make("DepthBuffer", width, height);

	BaseTexture::TextureForm textureForm;

	textureForm.mipmapLevel = 0;
	textureForm.width = width;
	textureForm.height = height;
	textureForm.border = 0;
	textureForm.textureData = nullptr;
	textureForm.sWrap = GL_CLAMP_TO_EDGE;
	textureForm.tWrap = GL_CLAMP_TO_EDGE;
	textureForm.minFilter = GL_NEAREST;
	textureForm.maxFilter = GL_NEAREST;

	textureForm.internalFormat = GL_RGB16F;
	textureForm.texelFormat = GL_RGB;
	textureForm.texelDataFormat = GL_FLOAT;
	BaseTexturePtr posTex = CustomTexture::Make("PosBuffer", textureForm);
	BaseTexturePtr normalTex = CustomTexture::Make("NormalBuffer", textureForm);

	textureForm.internalFormat = GL_RGBA;
	textureForm.texelFormat = GL_RGBA;
	textureForm.texelDataFormat = GL_UNSIGNED_BYTE;
	BaseTexturePtr ambientTex = CustomTexture::Make("AmbientBuffer", textureForm);
	BaseTexturePtr diffuseTex = CustomTexture::Make("DiffuseBuffer", textureForm);
	BaseTexturePtr specularTex = CustomTexture::Make("SpecularBuffer", textureForm);
	
	Error::Check("Before G Buffer Frame Buffer Generation");

	GenFrameBuffer(width, height, depthTex, { posTex, normalTex, ambientTex, diffuseTex, specularTex });

	Error::Check("After G Buffer Frame Buffer Generation");
}

GBuffer::~GBuffer()
{
	FrameBuffer::~FrameBuffer();
}

void GBuffer::LoadTextures(ShaderPtr shader)
{
	const std::string variablesNames[5] = {"positionMap", "normalMap", "ambientMap", "diffuseMap", "specularMap"};
	int i = 0;

	for (BaseTexturePtr texture : colorTextures)
	{
		texture->Load(shader, variablesNames[i]);
		i++;
	}
}

void GBuffer::UnloadTextures(ShaderPtr shader)
{
	for (BaseTexturePtr texture : colorTextures)
	{
		texture->Unload(shader);
	}
}