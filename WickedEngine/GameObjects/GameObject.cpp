#include "GameObject.h"

GameObject::GameObject(std::string name) : ownedTransform(*this), transform(ownedTransform), name(name) {}

GameObject::~GameObject()
{
	while (!components.empty())
	{
		MonoBehaviour* component = components.front();
		components.pop_front();
		delete component;
	}

	while (!children.empty())
	{
		GameObject* child = children.front();
		children.pop_front();
		delete child;
	}
}

glm::mat4 GameObject::Draw(const glm::mat4& baseMatrix)
{
	const glm::mat4 mvp = transform.getTransformMatrix(baseMatrix);

	for (Renderer* renderComponent : renderQueue)
	{
		renderComponent->Draw(mvp);
	}

	return mvp;
}

void GameObject::AddToRenderQueue(Renderer* newRenderer)
{
	renderQueue.push_back(newRenderer);
}

std::list<GameObject*> GameObject::GetChildren()
{
	return children;
}

void GameObject::AddChild(GameObject* child)
{
	children.push_back(child);
}

GameObject* GameObject::CreateEmptyChild(std::string name)
{
	GameObject* newChildren = new GameObject();

	AddChild(newChildren);

	return newChildren;
}
