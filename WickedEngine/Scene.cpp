#include "Scene.h"

void Scene::DrawScene(const glm::mat4x4& originalMatrix)
{
	if (root.empty()) return;

	std::list<GameObjectPtr> queue;
	std::list<glm::mat4x4> transformationMatrix;

	for (GameObjectPtr gameObject : root)
	{
		queue.push_back(gameObject);
		//TODO change to pointer so the list is smaller
		transformationMatrix.push_back(originalMatrix);
	}

	while (!queue.empty())
	{
		GameObjectPtr currentObject = queue.front();
		glm::mat4x4 currentMatrix = transformationMatrix.front();

		queue.pop_front();
		transformationMatrix.pop_front();

		currentMatrix = currentObject->Draw(currentMatrix);
		currentObject->Update();

		std::list<GameObjectPtr> childList = currentObject->GetChildren();

		for (auto i = childList.rbegin(); i != childList.rend(); i++)
		{
			queue.push_front(*i);
			transformationMatrix.push_front(currentMatrix);
		}
	}
}

GameObjectPtr Scene::CreateNewGameObject(std::string gameObjectName, GameObjectPtr parent)
{
	GameObjectPtr newGameObject = GameObject::Make(gameObjectName);

	if (parent == nullptr)
	{
		root.push_back(newGameObject);
	}
	else
	{
		parent->AddChild(newGameObject);
	}

	return newGameObject;
}

void Scene::printScene()
{
	if (root.empty()) return;

	std::list<GameObjectPtr> queue;
	std::list<unsigned int> level;

	for (GameObjectPtr gameObject : root)
	{
		queue.push_back(gameObject);
		level.push_back(0);
	}

	while (!queue.empty())
	{
		GameObjectPtr currentObject = queue.front();
		unsigned int currentLevel = level.front();

		queue.pop_front();
		level.pop_front();

		for (int i = 0; i < currentLevel; i++)
		{
			std::cout << '\t';
		}

		std::cout << currentObject->name << std::endl;

		std::list<GameObjectPtr> childList = currentObject->GetChildren();

		for (auto i = childList.rbegin(); i != childList.rend(); i++)
		{
			queue.push_front(*i);
			level.push_front(currentLevel + 1);
		}
	}
}