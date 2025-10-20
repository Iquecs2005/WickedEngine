#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	using Light::lightIntensity;

	friend class GameObject;
};

