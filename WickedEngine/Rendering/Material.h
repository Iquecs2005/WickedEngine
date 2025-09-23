#include <memory>

class Material;
using MaterialPtr = std::shared_ptr<Material>;

#pragma once

#include "shader.h"

class Material
{
public:
	static inline MaterialPtr Make(ShaderPtr shader = nullptr);
	void AttachShader(ShaderPtr shader);
	ShaderPtr GetShader();
private:
	Material(ShaderPtr shader = nullptr);

	ShaderPtr currentShader;
};

MaterialPtr Material::Make(ShaderPtr shader)
{
	return MaterialPtr(new Material(shader));
}