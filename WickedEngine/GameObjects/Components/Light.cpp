#include "Light.h"

Light* Light::currentLight = nullptr;

void Light::LoadLights(ShaderPtr currentShader)
{
	currentShader->SetUniform("lpos", currentLight->gameObject->transform.position);
}