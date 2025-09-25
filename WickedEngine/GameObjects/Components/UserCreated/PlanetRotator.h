#pragma once

#include "../MonoBehaviour.h"

class PlanetRotator : public MonoBehaviour
{
public:
	float rotatingSpeed = 4;

	PlanetRotator(GameObject* gameobject) : MonoBehaviour(gameobject) {}
	~PlanetRotator() {};
	void Update() override;

private:

};