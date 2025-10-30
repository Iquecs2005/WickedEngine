#pragma once

#include "../../General/Vector3.h"
#include "../../General/Vector2.h"

struct Vertex3D
{
	float x, y, z;
	float nx, ny, nz;
	float tx, ty, tz;
	float s, t;

	Vertex3D();
	Vertex3D(float x, float y, float z,
			 float nx, float ny, float nz,
			 float tx, float ty, float tz,
			 float s, float t);
	Vertex3D(Vector3 coords, Vector3 normal, Vector3 tangent, Vector2 texcoords);

	float* GetData();
};

