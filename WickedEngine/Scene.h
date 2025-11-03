#pragma once

#include "GameObjects/GameObject.h"

class Scene
{
public:
	std::string name;

	Scene(const std::string& name = "Scene");
	~Scene();

	//GameObjectPtr CreateNewGameObject(std::string gameObjectName = "GameObject", GameObject* parent = nullptr);
	
	//void UpdateScene();
	//void DrawScene();
	//void printScene();
private:
	std::list<GameObjectShared> root;
};

