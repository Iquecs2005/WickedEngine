#include <memory>

class FogModifier;
using FogModifierPtr = std::shared_ptr<FogModifier>;

#pragma once

#include "RenderModifier.h"
#include "../General/Color.h"

class FogModifier : public RenderModifier
{
public:
	float fogDensity;
	ColorPtr fogColor;

	inline static FogModifierPtr Make(float fogDensity, ColorPtr fogColor);

	void LoadModifier(ShaderPtr shader) override;
	void UnloadModifier(ShaderPtr shader) override;
protected:
	inline FogModifier(float fogDensity, ColorPtr fogColor);
};

inline FogModifierPtr FogModifier::Make(float fogDensity, ColorPtr fogColor)
{
	return FogModifierPtr(new FogModifier(fogDensity, fogColor));
}

inline FogModifier::FogModifier(float fogDensity, ColorPtr fogColor)
	: RenderModifier(), fogDensity(fogDensity), fogColor(fogColor)
{
	
}