#include <memory>

class GameObject;

#pragma once

#include <list>
#include <string>
#include <iostream>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../Rendering/shader.h"
#include "Components/MonoBehaviour.h"
#include "Components/Renderer.h"

class Scene;

class GameObject
{
public:
	std::string name;

	Transform& transform;
	std::list<ShapePtr> geometryList;

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
		//MonoBehaviour* monoComponent = dynamic_cast<MonoBehaviour*>(newComponent);

		/*if (!monoComponent)
		{
			std::cerr << "Trying to attach a non-Component to a GameObject";
			delete newComponent;
			return nullptr;
		}*/

		components.push_front(newComponent);
		return newComponent;
	}

	void AddToRenderQueue(Renderer* newRenderer);

	std::list<GameObject*> GetChildren();
	void AddChild(GameObject* child);
	GameObject* CreateEmptyChild(std::string name = "Child");

	friend class Scene;

private:
	Transform ownedTransform;
	std::list<MonoBehaviour*> components;
	std::list<Renderer*> renderQueue;
	std::list<GameObject*> children;

	GameObject(std::string name = "GameObject");
	~GameObject();
};

