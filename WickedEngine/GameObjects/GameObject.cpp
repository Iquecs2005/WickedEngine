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
	GameObject* newChildren = new GameObject(name);

	AddChild(newChildren);

	return newChildren;
}
