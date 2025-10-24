#pragma once

#include "Light.h"
#include "../GameObject.h"

class PointLight : public Light
{
public:
	float lightAttConstantCoefficient;
	float lightAttLinearCoefficient;
	float lightAttQuadraticCoefficient;

	void LoadLight(ShaderPtr currentShader) override;

	friend class GameObject;
protected:
	PointLight(GameObject* gameObject);
};