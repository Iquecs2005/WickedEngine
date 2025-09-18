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

std::list<GameObjectPtr> GameObject::getChildren()
{
	return children;
}

void GameObject::addChild(GameObjectPtr child)
{
	children.push_back(child);
}

GameObjectPtr GameObject::createEmptyChild(std::string name)
{
	GameObjectPtr newChildren = GameObject::Make(name);

	addChild(newChildren);

	return newChildren;
}
