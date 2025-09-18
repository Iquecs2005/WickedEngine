#pragma once

#include "GameObjects/GameObject.h"

class Scene
{
public:
	void DrawScene(const glm::mat4x4& originalMatrix, const ShaderPtr& shd);
	GameObjectPtr CreateNewGameObject(std::string gameObjectName = "GameObject", GameObjectPtr parent = nullptr);
	void printScene();
private:
	std::list<GameObjectPtr> root;
};

