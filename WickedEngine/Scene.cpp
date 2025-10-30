#include "Scene.h"
#include "GameObjects/Components/Camera.h"
#include "Rendering/MVPMatrix.h"
#include "GameObjects/Components/Light.h"

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

	std::list<GameObject*> stack;
	std::list<MVPMatrixPtr> transformationMatrix;

	Camera::getMainCamera()->LoadCamera();
	glm::mat4 a = Camera::getMainCamera()->GetViewMatrix();
	glm::mat4 b = Camera::getMainCamera()->GetViewMatrix();
	MVPMatrixPtr baseMatrix = MVPMatrix::Make(glm::mat4(1.0f),
											  Camera::getMainCamera()->GetViewMatrix(),
											  Camera::getMainCamera()->GetProjectionMatrix());

	for (const auto& gameObject : root)
	{
		stack.push_back(gameObject);
		transformationMatrix.push_back(baseMatrix);
	}

	while (!stack.empty())
	{
		GameObject* currentObject = stack.front();
		MVPMatrixPtr currentMvp = transformationMatrix.front();

		stack.pop_front();
		transformationMatrix.pop_front();

		currentMvp = currentObject->Draw(currentMvp);
		currentObject->Update();

		std::list<GameObject*> childList = currentObject->GetChildren();

		for (auto i = childList.rbegin(); i != childList.rend(); i++)
		{
			stack.push_front(*i);
			transformationMatrix.push_front(currentMvp);
		}
	}

	Camera::getMainCamera()->UnloadCamera();
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