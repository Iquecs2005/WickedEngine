#include "Vertex3D.h"

Vertex3D::Vertex3D()
	: x(0), y(0), z(0),
	nx(0), ny(0), nz(0),
	tx(0), ty(0), tz(0),
	s(0), t(0)
{

}

Vertex3D::Vertex3D(float x, float y, float z, float nx, float ny, float nz, float tx, float ty, float tz, float s, float t)
	: x(x), y(y), z(z),
	nx(nx), ny(ny), nz(nz),
	tx(tx), ty(ty), tz(tz),
	s(s), t(t)
{

}

Vertex3D::Vertex3D(Vector3 coords, Vector3 normal, Vector3 tangent, Vector2 texcoords)
	: x(coords.x), y(coords.y), z(coords.z), 
	  nx(normal.x), ny(normal.y), nz(normal.z),
	  tx(tangent.x), ty(tangent.y), tz(tangent.z),
	  s(texcoords.x), t(texcoords.y)
{
	
}

float* Vertex3D::GetData()
{
	float data[] = {x, y, z, nx, ny, nz, tx, ty, tz, s, t};
	return data;
}