#include <memory>

class Material;
using MaterialPtr = std::shared_ptr<Material>;

#pragma once

#include "shader.h"

class Material
{
public:
	static inline MaterialPtr Make();
	void AttachShader(ShaderPtr shader);
	ShaderPtr GetShader();
private:
	Material();

	ShaderPtr currentShader;
};

MaterialPtr Material::Make()
{
	return MaterialPtr(new Material());
}
