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

	static inline MaterialPtr Make(ShaderPtr shader = nullptr, TexturePtr decalTexture = nullptr, TexturePtr glossTexture = nullptr);

	void Load();
	void Unload();
	void AttachShader(ShaderPtr shader);
	void AttachDecalTexture(TexturePtr texture);
	void AttachGlossTexture(TexturePtr texture);

	ShaderPtr GetShader();
	TexturePtr GetDecalTexture();
	TexturePtr GetGlossTexture();
private:
	Material(ShaderPtr shader = nullptr, TexturePtr decalTexture = nullptr, TexturePtr glossTexture = nullptr);

	ShaderPtr currentShader;
	TexturePtr decalTexture;
	TexturePtr glossTexture;
};

MaterialPtr Material::Make(ShaderPtr shader, TexturePtr decalTexture, TexturePtr glossTexture)
{
	return MaterialPtr(new Material(shader, decalTexture, glossTexture));
}