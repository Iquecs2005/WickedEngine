#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <cmath>

Sphere::Sphere(unsigned int nstack, unsigned int nslice)
	: Mesh3D(GetVerticeList(nstack, nslice), GetIncidenceList(nstack, nslice))
{

}

GridMeshPtr Sphere::CreateGrid(unsigned int nstack, unsigned int nslice)
{
	grid = GridMesh::Make(nstack, nslice);

	std::vector<VertexData3D>& vertexDataList = grid->GetVerticeList();
	for (VertexData3D& vertexData : vertexDataList)
	{
		float theta = vertexData.x * 2 * M_PI;
		float phi = vertexData.y * M_PI;

		vertexData.x = sin(theta) * sin(M_PI - phi);
		vertexData.y = cos(M_PI - phi);
		vertexData.z = cos(theta) * sin(M_PI - phi);

		vertexData.nx = vertexData.x;
		vertexData.ny = vertexData.y;
		vertexData.nz = vertexData.z;
	}

	return grid;
}