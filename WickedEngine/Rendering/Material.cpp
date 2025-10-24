#include "Material.h"

#include <glad/gl.h>
#include "../error.h"

void Material::Load()
{
	currentShader->UseProgram();

	currentShader->SetUniform("materialAmbientColor", (glm::vec4)*ambientColor);
	currentShader->SetUniform("materialDiffuseColor", (glm::vec4)*diffuseColor);
	currentShader->SetUniform("materialSpecularColor", (glm::vec4)*specularColor);

	currentShader->SetUniform("spotCoeficient", spotCoeficient);

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
	: ambientColor(Color::Make()), diffuseColor(Color::Make()), specularColor(Color::Make())
{
	ambientColor = Color::white;
	diffuseColor = Color::white;
	specularColor = Color::white;

	spotCoeficient = 16;

	AttachShader(shader);
	if (texture == nullptr)
	{
		texture = Texture::GetDefaultTexture();
	}
	AttachTexture(texture);
}