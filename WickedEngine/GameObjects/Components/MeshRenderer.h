#pragma once

#include <iostream>
#include "MonoBehaviour.h"
#include "../../Geometry/Shape.h"

class MeshRenderer : public MonoBehaviour
{
public:
	MeshRenderer(GameObject* gameObject) : MonoBehaviour(gameObject) {}

	ShapePtr mesh;

	void Update()
	{
		mesh->Draw();
	}

	~MeshRenderer() {};
};

