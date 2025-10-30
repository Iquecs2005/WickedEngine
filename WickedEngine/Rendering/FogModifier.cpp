#include "FogModifier.h"

void FogModifier::LoadModifier(ShaderPtr shader)
{
	shader->SetUniform("fogDensity", fogDensity);
	shader->SetUniform("fogColor", (glm::vec4)*fogColor);
}

void FogModifier::UnloadModifier(ShaderPtr shader)
{
	shader->SetUniform("fogDensity", 0.0f);
	shader->SetUniform("fogColor", (glm::vec4)*Color::white);
}