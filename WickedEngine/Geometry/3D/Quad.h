#include <memory>

class Quad;
using QuadPtr = std::shared_ptr<Quad>;

#pragma once

#include "Mesh3D.h"

class Quad : public Mesh3D
{
	Quad() : Mesh3D(
		{
			Vertex3D(Vector3(-1, -1, 0), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(0, 0)),
			Vertex3D(Vector3(-1, 1, 0), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(0, 1)),
			Vertex3D(Vector3(1, -1, 0), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(1, 0)),
			Vertex3D(Vector3(1,  1, 0), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(1, 1))
		}
		,
		{
			0, 2, 1, 2, 3, 1
		}
	)
	{
	}
public:
	static inline QuadPtr Make();
};

inline QuadPtr Quad::Make()
{
	return QuadPtr(new Quad());
}

