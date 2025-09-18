#include <memory>

class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;

#pragma once

#include <list>
#include <string>
#include <iostream>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../shader.h"
#include "Components/MonoBehaviour.h"

class GameObject
{
public:
	std::string name;

	Transform& transform;
	std::list<ShapePtr> geometryList;

	GameObject(std::string name = "GameObject");
	~GameObject();
	static inline GameObjectPtr Make(std::string name = "GameObject");

	void Update()
	{
		for (MonoBehaviour* component : components)
		{
			component->Update();
		}
	}

	glm::mat4 Draw(const glm::mat4& baseMatrix, const ShaderPtr& shd)
	{
		const glm::mat4 M = transform.getTransformMatrix(baseMatrix);
		shd->SetUniform("M", M);

		for (MonoBehaviour* component : components)
		{
			component->Update();
		}

		return M;
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

	std::list<GameObjectPtr> getChildren();
	void addChild(GameObjectPtr child);
	GameObjectPtr createEmptyChild(std::string name = "Child");

private:
	Transform ownedTransform;
	std::list<MonoBehaviour*> components;
	std::list<GameObjectPtr> children;
};

inline GameObjectPtr GameObject::Make(std::string name)
{
	return GameObjectPtr(new GameObject(name));
}

