#pragma once

#include "glm/glm.hpp"
#include "MonoBehaviour.h"
#include "../../Rendering/MVPMatrix.h"

class Renderer : public MonoBehaviour
{
public:
	Renderer(GameObject* gameObject);
	virtual void Draw(const MVPMatrixPtr mvp) {};
};

