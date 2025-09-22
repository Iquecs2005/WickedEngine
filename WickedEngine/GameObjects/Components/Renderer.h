#pragma once

#include "glm/glm.hpp"
#include "MonoBehaviour.h"

class Renderer : public MonoBehaviour
{
public:
	Renderer(GameObject* gameObject);
	virtual void Draw(glm::mat4x4 mvp) {};
};

