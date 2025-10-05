#include "Material.h"

#include <glad/gl.h>
#include "../error.h"

void Material::Load()
{
	currentShader->UseProgram();
	currentShader->ActiveTexture(texture->GetTextureName().c_str());
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
}

void Material::Unload()
{
	currentShader->DeactiveTexture();
}

void Material::AttachShader(ShaderPtr shader)
{
	currentShader = shader;
}

void Material::AttachTexture(TexturePtr texture)
{
	this->texture = texture;
}

ShaderPtr Material::GetShader()
{
	return currentShader;
}

TexturePtr Material::GetTexture()
{
	return texture;
}

Material::Material(ShaderPtr shader, TexturePtr texture)
{
	AttachShader(shader);
	if (texture == nullptr)
	{
		texture = Texture::GetDefaultTexture();
	}
	AttachTexture(texture);
}