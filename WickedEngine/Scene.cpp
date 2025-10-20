#include "Scene.h"
#include "GameObjects/Components/Camera.h"

Scene::Scene(const std::string& name)
{
	this->name = name;
}

Scene::~Scene()
{
	std::cout << "Deleting Scene" << std::endl;

	while (!root.empty())
	{
		GameObject* component = root.front();
		root.pop_front();
		delete component;
	}
}

void Scene::DrawScene()
{
	if (root.empty()) return;

	std::list<GameObject*> queue;
	std::list<glm::mat4x4> transformationMatrix;

	glm::mat4x4 cameraMatrix = Camera::getMainCamera()->GetProjectionMatrix();
	cameraMatrix = cameraMatrix * Camera::getMainCamera()->GetViewMatrix();

	for (const auto& gameObject : root)
	{
		queue.push_back(gameObject);
		//TODO change to pointer so the list is smaller
		transformationMatrix.push_back(cameraMatrix);
	}

	while (!queue.empty())
	{
		GameObject* currentObject = queue.front();
		glm::mat4x4 currentMatrix = transformationMatrix.front();

		queue.pop_front();
		transformationMatrix.pop_front();

		currentMatrix = currentObject->Draw(currentMatrix);
		currentObject->Update();

		std::list<GameObject*> childList = currentObject->GetChildren();

		for (auto i = childList.rbegin(); i != childList.rend(); i++)
		{
			queue.push_front(*i);
			transformationMatrix.push_front(currentMatrix);
		}
	}
}

GameObject* Scene::CreateNewGameObject(std::string gameObjectName, GameObject* parent)
{
	GameObject* newGameObject = new GameObject(gameObjectName);

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
	std::cout << name << ":" << std::endl;

	if (root.empty()) return;

	std::list<GameObject*> queue;
	std::list<unsigned int> level;

	for (GameObject* gameObject : root)
	{
		queue.push_back(gameObject);
		level.push_back(0);
	}

	while (!queue.empty())
	{
		GameObject* currentObject = queue.front();
		unsigned int currentLevel = level.front();

		queue.pop_front();
		level.pop_front();

		for (int i = 0; i < (currentLevel + 1) * 2; i++)
		{
			std::cout << ' ';
		}

		if (currentLevel > 0) std::cout << "-";
		else std::cout << "-";

		std::cout << currentObject->name << std::endl;

		std::list<GameObject*> childList = currentObject->GetChildren();

		for (auto i = childList.rbegin(); i != childList.rend(); i++)
		{
			queue.push_front(*i);
			level.push_front(currentLevel + 1);
		}
	}

	std::cout << std::endl;
}