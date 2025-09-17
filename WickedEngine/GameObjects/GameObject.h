class GameObject;

#pragma once

#include <list>
#include <memory>
#include <iostream>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../shader.h"
#include "Components/MonoBehaviour.h"

class GameObject
{
public:
	Transform& transform;
	std::list<ShapePtr> geometryList;

	GameObject() : ownedTransform(*this), transform(ownedTransform)
	{
		transform.position = Vector3();
	}

	~GameObject()
	{
		while (!components.empty())
		{
			MonoBehaviour* component = components.front();
			components.pop_front();
			delete component;
		}
	}

	void Update()
	{
		for (MonoBehaviour* component : components)
		{
			component->Update();
		}
	}

	void Draw(const glm::mat4 baseMatrix, const ShaderPtr& shd)
	{
		const glm::mat4 M = transform.getTransformMatrix(baseMatrix);
		shd->SetUniform("M", M);

		for (MonoBehaviour* component : components)
		{
			component->Update();
		}
	}

	template <typename ComponentType>
	ComponentType* AttachComponent()
	{
		ComponentType* newComponent = new ComponentType();
		MonoBehaviour* monoComponent = dynamic_cast<MonoBehaviour*>(newComponent);

		if (!monoComponent)
		{
			std::cerr << "Trying to attach a non-Component to a GameObject";
			delete newComponent;
			return nullptr;
		}

		components.push_front(monoComponent);
		return newComponent;
	}

private:
	Transform ownedTransform;
	std::list<MonoBehaviour*> components;
};
