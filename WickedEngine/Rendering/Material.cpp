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

	currentShader->ActiveTexture("gloss");
	glBindTexture(GL_TEXTURE_2D, glossTexture->GetTextureId());
	currentShader->ActiveTexture("decal");
	glBindTexture(GL_TEXTURE_2D, decalTexture->GetTextureId());
}

void Material::Unload()
{
	currentShader->DeactiveTexture();
	currentShader->DeactiveTexture();
}

void Material::AttachShader(ShaderPtr shader)
{
	currentShader = shader;
}

void Material::AttachDecalTexture(TexturePtr texture)
{
	if (texture == nullptr)
	{
		texture = Texture::GetDefaultTexture();
	}

	decalTexture = texture;
}

void Material::AttachGlossTexture(TexturePtr texture)
{
	if (texture == nullptr)
	{
		texture = Texture::GetDefaultTexture();
	}

	glossTexture = texture;
}

ShaderPtr Material::GetShader()
{
	return currentShader;
}

TexturePtr Material::GetDecalTexture()
{
	return decalTexture;
}

TexturePtr Material::GetGlossTexture()
{
	return glossTexture;
}

Material::Material(ShaderPtr shader, TexturePtr decalTexture, TexturePtr glossTexture)
	: ambientColor(Color::Make()), diffuseColor(Color::Make()), specularColor(Color::Make())
{
	ambientColor = Color::white;
	diffuseColor = Color::white;
	specularColor = Color::white;

	spotCoeficient = 16;

	AttachShader(shader);
	AttachDecalTexture(decalTexture);
	AttachGlossTexture(glossTexture);
}