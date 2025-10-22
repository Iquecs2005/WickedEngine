#include <memory>

class GridMesh;
using GridMeshPtr = std::shared_ptr<GridMesh>;

#pragma once

#include "Mesh3D.h"

class GridMesh
{
public:
	inline GridMeshPtr Make(unsigned int nX, unsigned int nY);

	const unsigned int nVertices;
	const unsigned int nVerticesX;
	const unsigned int nVerticesY;
	const unsigned int nTriangles;
	
	const std::vector<VertexData3D> verticeList;
	const std::vector<unsigned int> incidenceList;
protected:
	GridMesh(unsigned int nX, unsigned int nY);
};

GridMeshPtr GridMesh::Make(unsigned int nX, unsigned int nY)
{
	return GridMeshPtr(new GridMesh(nX, nY));
}