#include <memory>

class GameObject;
using GameObjectPtr = std::weak_ptr<GameObject>;
using GameObjectShared = std::shared_ptr<GameObject>;

#pragma once

#include <list>
#include <string>
#include <iostream>
#include "Components/Transform.h"
#include "../Geometry/Shape.h"
#include "../Rendering/shader.h"
#include "Components/MonoBehaviour.h"
#include "Components/Renderer.h"
#include "../Rendering/MVPMatrix.h"

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

	MVPMatrixPtr Draw(const MVPMatrixPtr baseMatrix);

	template<typename ComponentType>
	ComponentType* AttachComponent()
	{
		ComponentType* newComponent = new ComponentType(this);
		components.push_front(newComponent);
		return newComponent;
	}

	void AddToRenderQueue(Renderer* newRenderer);

	//TO DO change to unique ptr
	std::list<GameObjectPtr> GetChildren();
	void AddChild(GameObjectShared child);
	GameObjectPtr CreateEmptyChild(std::string name = "Child");

	friend class Scene;

private:
	Transform ownedTransform;
	//TO DO change to unique ptr
	std::list<MonoBehaviour*> components;
	std::list<Renderer*> renderQueue;
	std::list<GameObjectShared> children;

	GameObject(std::string name = "GameObject");
	~GameObject();

	//inline static GameObjectShared Make(std::string name);
};

//inline GameObjectShared GameObject::Make(std::string name)
//{
//	return GameObjectShared(new GameObject(name));
//}

