#include "Material.h"

void Material::AttachShader(ShaderPtr shader)
{
	currentShader = shader;
}

ShaderPtr Material::GetShader()
{
	return currentShader;
}

Material::Material(ShaderPtr shader)
{
	AttachShader(shader);
}