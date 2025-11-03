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

MVPMatrixPtr GameObject::Draw(const MVPMatrixPtr baseMatrix)
{
	glm::mat4 modelMatrix = transform.getTransformMatrix();
	MVPMatrixPtr mvp = MVPMatrix::Make(modelMatrix, baseMatrix);

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
	std::list<GameObjectPtr> returnList;

	for (GameObjectShared gameObject : children)
	{
		returnList.push_back(gameObject);
	}

	return returnList;
}

void GameObject::AddChild(GameObjectShared child)
{
	children.push_back(child);
	child->transform.SetParent(&transform);
}

//GameObjectPtr GameObject::CreateEmptyChild(std::string name)
//{
//	GameObjectShared newChildren = GameObject::Make(name);
//
//	AddChild(newChildren);
//
//	return GameObjectPtr(newChildren);
//}
