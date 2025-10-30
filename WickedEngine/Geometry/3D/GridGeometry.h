#include <memory>

class GridGeometry;
using GridGeometryPtr = std::shared_ptr<GridGeometry>;

#pragma once

#include "Mesh3D.h"
#include "GridMesh.h"

class GridGeometry : public Mesh3D
{
public:
	static inline GridGeometryPtr Make(unsigned int nX, unsigned int nY);
protected:
	GridGeometry(unsigned int nx, unsigned int ny);
private:
	GridMeshPtr grid = nullptr;

	inline const std::vector<Vertex3D>& GetVerticeList(unsigned int nx, unsigned int ny);
	inline const std::vector<unsigned int>& GetIncidenceList(unsigned int nx, unsigned int ny);
};

inline GridGeometryPtr GridGeometry::Make(unsigned int nX, unsigned int nY)
{
	return GridGeometryPtr(new GridGeometry(nX, nY));
}

inline const std::vector<Vertex3D>& GridGeometry::GetVerticeList(unsigned int nx, unsigned int ny)
{
	if (grid == nullptr)
		grid = GridMesh::Make(nx, ny);
	return grid->GetVerticeList();
}

inline const std::vector<unsigned int>& GridGeometry::GetIncidenceList(unsigned int nx, unsigned int ny)
{
	if (grid == nullptr)
		grid = GridMesh::Make(nx, ny);
	return grid->GetIncidenceList();
}

