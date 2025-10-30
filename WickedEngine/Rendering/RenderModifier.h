#include <memory>

class RenderModifier;
using RenderModifierPtr = std::shared_ptr<RenderModifier>;

#pragma once

#include "shader.h"

class RenderModifier
{
public:
	virtual void LoadModifier(ShaderPtr shader) = 0;
	virtual void UnloadModifier(ShaderPtr shader) = 0;
protected:
	RenderModifier() {};
};