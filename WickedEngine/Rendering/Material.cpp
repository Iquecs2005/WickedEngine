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

	normalMap->Load(currentShader, "normalMap");
	glossTexture->Load(currentShader, "gloss");
	decalTexture->Load(currentShader, "decal");
}

void Material::Unload()
{
	normalMap->Unload(currentShader);
	glossTexture->Unload(currentShader);
	decalTexture->Unload(currentShader);
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

void Material::AttachNormalMap(TexturePtr texture)
{
	if (texture == nullptr)
	{
		texture = Texture::GetDefaultNormalMap();
	}

	normalMap = texture;
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

Material::Material(ShaderPtr shader, TexturePtr decalTexture, TexturePtr glossTexture, TexturePtr normalMap)
	: ambientColor(Color::Make()), diffuseColor(Color::Make()), specularColor(Color::Make())
{
	ambientColor = Color::white;
	diffuseColor = Color::white;
	specularColor = Color::white;

	spotCoeficient = 16;

	AttachShader(shader);
	AttachDecalTexture(decalTexture);
	AttachGlossTexture(glossTexture);
	AttachNormalMap(normalMap);
}