#include <memory>

class Material;
using MaterialPtr = std::shared_ptr<Material>;

#pragma once

#include "shader.h"
#include "Texture.h"
#include "../General/Color.h"

class Material
{
public:
	ColorPtr ambientColor;
	ColorPtr diffuseColor;
	ColorPtr specularColor;

	float spotCoeficient;

	static inline MaterialPtr Make(ShaderPtr shader = nullptr, TexturePtr texture = nullptr);

	void Load();
	void Unload();
	void AttachShader(ShaderPtr shader);
	void AttachTexture(TexturePtr texture);

	ShaderPtr GetShader();
	TexturePtr GetTexture();
private:
	Material(ShaderPtr shader = nullptr, TexturePtr texture = nullptr);

	ShaderPtr currentShader;
	TexturePtr texture;
};

MaterialPtr Material::Make(ShaderPtr shader, TexturePtr texture)
{
	return MaterialPtr(new Material(shader, texture));
}