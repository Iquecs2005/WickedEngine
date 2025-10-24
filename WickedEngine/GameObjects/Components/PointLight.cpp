#include "PointLight.h"

PointLight::PointLight(GameObject* gameObject) : Light(gameObject)
{
	lightAttConstantCoefficient = 0.90;
	lightAttLinearCoefficient = 0.10f;
	lightAttQuadraticCoefficient = 0.01f;
}

void PointLight::LoadLight(ShaderPtr currentShader)
{
	currentShader->SetUniform("lightPos", (glm::vec4)gameObject->transform.position);

	currentShader->SetUniform("lightAttConstantCoefficient", lightAttConstantCoefficient);
	currentShader->SetUniform("lightAttLinearCoefficient", lightAttLinearCoefficient);
	currentShader->SetUniform("lightAttQuadraticCoefficient", lightAttQuadraticCoefficient);
}