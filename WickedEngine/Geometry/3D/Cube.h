#include <memory>

class Cube;
using CubePtr = std::shared_ptr<Cube>;

#pragma once

#include "Mesh3D.h"

class Cube : public Mesh3D
{
protected:
	Cube() : Mesh3D( 
		{
			//Far face
			Vertex3D(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(1, 0)),
			Vertex3D(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(1, 1)),
			Vertex3D(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(0, 0)),
			Vertex3D(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector3(-1, 0, 0), Vector2(0, 1)),
			//Left face
			Vertex3D(Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0, 0, 1), Vector2(0, 0)),
			Vertex3D(Vector3(-0.5f,  0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0, 0, 1), Vector2(0, 1)),
			Vertex3D(Vector3(-0.5f, -0.5f,  0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0, 0, 1), Vector2(1, 0)),
			Vertex3D(Vector3(-0.5f,  0.5f,  0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0, 0, 1), Vector2(1, 1)),
			//Right face
			Vertex3D(Vector3(0.5f, -0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0, 0, -1), Vector2(1, 0)),
			Vertex3D(Vector3(0.5f,  0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0, 0, -1), Vector2(1, 1)),
			Vertex3D(Vector3(0.5f, -0.5f,  0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0, 0, -1), Vector2(0, 0)),
			Vertex3D(Vector3(0.5f,  0.5f,  0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0, 0, -1), Vector2(0, 1)),
			//Front face
			Vertex3D(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f,  0.0f,  1.0f), Vector3(1, 0, 0), Vector2(0, 0)),
			Vertex3D(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f,  0.0f,  1.0f), Vector3(1, 0, 0), Vector2(0, 1)),
			Vertex3D(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f,  0.0f,  1.0f), Vector3(1, 0, 0), Vector2(1, 0)),
			Vertex3D(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f,  0.0f,  1.0f), Vector3(1, 0, 0), Vector2(1, 1)),
			//Up face
			Vertex3D(Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f,  1.0f,  0.0f), Vector3(1, 0, 0), Vector2(0, 0)),
			Vertex3D(Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f,  1.0f,  0.0f), Vector3(1, 0, 0), Vector2(0, 1)),
			Vertex3D(Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f,  1.0f,  0.0f), Vector3(1, 0, 0), Vector2(1, 0)),
			Vertex3D(Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f,  1.0f,  0.0f), Vector3(1, 0, 0), Vector2(1, 1)),
			//Down face
			Vertex3D(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f,  0.0f), Vector3(1, 0, 0), Vector2(0, 0)),
			Vertex3D(Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, -1.0f,  0.0f), Vector3(1, 0, 0), Vector2(0, 1)),
			Vertex3D(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f,  0.0f), Vector3(1, 0, 0), Vector2(1, 0)),
			Vertex3D(Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, -1.0f,  0.0f), Vector3(1, 0, 0), Vector2(1, 1)),
		}
		,
		{
			//Far face
			2, 0, 1, 2, 1, 3,
			//Left face
			4, 6, 7, 4, 7, 5,
			//Right face
			10, 8, 9, 10, 9, 11,
			//Front face
			12, 14, 15, 12, 15, 13,
			//Up face
			16, 18, 19, 16, 19, 17,
			//Down face
			20, 22, 23, 20, 23, 21
		}
	) 
	{
	}
public:
	static inline CubePtr Make();
};

inline CubePtr Cube::Make()
{
	return CubePtr(new Cube());
}

