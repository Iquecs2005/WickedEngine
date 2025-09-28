#pragma once

#include "GameObjects/GameObject.h"

class Scene
{
public:
	~Scene();
	//void UpdateScene();
	void DrawScene();
	GameObject* CreateNewGameObject(std::string gameObjectName = "GameObject", GameObject* parent = nullptr);
	void printScene();
private:
	std::list<GameObject*> root;
};

