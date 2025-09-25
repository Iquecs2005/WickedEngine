#pragma once

#include "GameObjects/GameObject.h"

class Scene
{
public:
	//void UpdateScene();
	void DrawScene(const glm::mat4x4& originalMatrix);
	GameObjectPtr CreateNewGameObject(std::string gameObjectName = "GameObject", GameObjectPtr parent = nullptr);
	void printScene();
private:
	std::list<GameObjectPtr> root;
};

