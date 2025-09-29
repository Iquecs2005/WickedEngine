#pragma once

#include "GameObjects/GameObject.h"

class Scene
{
public:
	std::string name;

	Scene(const std::string& name = "Scene");
	~Scene();
	//void UpdateScene();
	void DrawScene();
	GameObject* CreateNewGameObject(std::string gameObjectName = "GameObject", GameObject* parent = nullptr);
	void printScene();
private:
	std::list<GameObject*> root;
};

