#pragma once

#include "Light.h"
#include "../GameObject.h"

class PointLight : public Light
{
public:
	using Light::lightIntensity;

	friend class GameObject;
protected:
	PointLight(GameObject* gameObject);
};