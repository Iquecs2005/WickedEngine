#include "Light.h"

Light* Light::currentLight = nullptr;

void Light::LoadLights(ShaderPtr currentShader)
{
	if (currentLight != nullptr)
	{
		currentLight->LoadLight(currentShader);
	}
}

void Light::LoadLight(ShaderPtr currentShader)
{
	currentShader->SetUniform("lightPos", (glm::vec4)currentLight->gameObject->transform.position);
}

Light::Light(GameObject* gameObject) : MonoBehaviour(gameObject)
{
	currentLight = this;
}