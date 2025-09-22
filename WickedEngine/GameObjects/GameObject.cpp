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

std::list<GameObjectPtr> GameObject::GetChildren()
{
	return children;
}

void GameObject::AddChild(GameObjectPtr child)
{
	children.push_back(child);
}

GameObjectPtr GameObject::CreateEmptyChild(std::string name)
{
	GameObjectPtr newChildren = GameObject::Make(name);

	AddChild(newChildren);

	return newChildren;
}
