class GameObject;

#pragma once

#include <list>
#include <memory>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../shader.h"

class GameObject
{
public:
	Transform& transform;
	std::list<std::shared_ptr<Shape>> geometryList;

	GameObject() : ownedTransform(*this), transform(ownedTransform)
	{
		transform.position = Vector3();
	}

	void Draw(const glm::mat4 baseMatrix, const ShaderPtr& shd)
	{
		const glm::mat4 M = transform.getTransformMatrix(baseMatrix);
		shd->SetUniform("M", M);

		for (auto shape : geometryList)
		{
			shape->Draw();
		}
	}

private:
	Transform ownedTransform;
};
