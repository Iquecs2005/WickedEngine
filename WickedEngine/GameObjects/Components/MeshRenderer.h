#pragma once

#include <iostream>
#include "MonoBehaviour.h"
#include "../../Geometry/Shape.h"

class MeshRenderer : public MonoBehaviour
{
public:
	ShapePtr mesh;

	void Update()
	{
		mesh->Draw();
	}

	~MeshRenderer() {};
};

