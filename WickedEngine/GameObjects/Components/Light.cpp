#include "Light.h"

Light* Light::currentLight = nullptr;

void Light::LoadLights(ShaderPtr currentShader)
{
	if (currentLight != nullptr)
	{
		currentShader->SetUniform("lightPos", (glm::vec4)currentLight->gameObject->transform.position);
	}
}