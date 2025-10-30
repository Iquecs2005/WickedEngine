#include <memory>

class GridMesh;
using GridMeshPtr = std::shared_ptr<GridMesh>;

#pragma once

#include "Mesh3D.h"

class GridMesh
{
public:
	static inline GridMeshPtr Make(unsigned int nX, unsigned int nY);
	inline std::vector<Vertex3D>& GetVerticeList();
	inline std::vector<unsigned int>& GetIncidenceList();

	const unsigned int nVertices;
	const unsigned int nVerticesX;
	const unsigned int nVerticesY;
	const unsigned int nTriangles;
	
protected:
	GridMesh(unsigned int nX, unsigned int nY);
private:
	std::vector<Vertex3D> verticeList;
	std::vector<unsigned int> incidenceList;

	inline unsigned int calculateIndex(unsigned int i, unsigned int j, unsigned int ny) const;
};

inline GridMeshPtr GridMesh::Make(unsigned int nX, unsigned int nY)
{
	return GridMeshPtr(new GridMesh(nX, nY));
}

inline std::vector<Vertex3D>& GridMesh::GetVerticeList()
{
	return verticeList;
}

inline std::vector<unsigned int>& GridMesh::GetIncidenceList()
{
	return incidenceList;
}

inline unsigned int GridMesh::calculateIndex(unsigned int i, unsigned int j, unsigned int ny) const
{
	return (unsigned int)(i * ny + j);
}