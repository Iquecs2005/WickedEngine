#include <memory>

class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;

#pragma once

#include <list>
#include <string>
#include <iostream>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../Rendering/shader.h"
#include "Components/MonoBehaviour.h"
#include "Components/Renderer.h"

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

	glm::mat4 Draw(const glm::mat4& baseMatrix);

	template<typename ComponentType>
	ComponentType* AttachComponent()
	{
		ComponentType* newComponent = new ComponentType(this);
		MonoBehaviour* monoComponent = dynamic_cast<MonoBehaviour*>(newComponent);

		/*if (!monoComponent)
		{
			std::cerr << "Trying to attach a non-Component to a GameObject";
			delete newComponent;
			return nullptr;
		}*/

		components.push_front(monoComponent);
		return newComponent;
	}

	void AddToRenderQueue(Renderer* newRenderer);

	std::list<GameObjectPtr> GetChildren();
	void AddChild(GameObjectPtr child);
	GameObjectPtr CreateEmptyChild(std::string name = "Child");

private:
	Transform ownedTransform;
	std::list<MonoBehaviour*> components;
	std::list<Renderer*> renderQueue;
	std::list<GameObjectPtr> children;
};

inline GameObjectPtr GameObject::Make(std::string name)
{
	return GameObjectPtr(new GameObject(name));
}

