#include "PointLight.h"

PointLight::PointLight(GameObject* gameObject) : Light(gameObject)
{
	lightAttConstantCoefficient = 1;
	lightAttLinearCoefficient = 0.005f;
	lightAttQuadraticCoefficient = 0.0001f;
}

void PointLight::LoadLight(ShaderPtr currentShader)
{
	currentShader->SetUniform("lightPos", (glm::vec4)gameObject->transform.position);

	currentShader->SetUniform("lightAttConstantCoefficient", lightAttConstantCoefficient);
	currentShader->SetUniform("lightAttLinearCoefficient", lightAttLinearCoefficient);
	currentShader->SetUniform("lightAttQuadraticCoefficient", lightAttQuadraticCoefficient);
}