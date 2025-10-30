#include <memory>

class Sphere;
using SpherePtr = std::shared_ptr<Sphere>;

#pragma once

#include "GridMesh.h"
#include "Mesh3D.h"

class Sphere : public Mesh3D
{
public:
	static inline SpherePtr Make(unsigned int nstack = 64, unsigned int nslice = 64);
protected:
	Sphere(unsigned int nstack, unsigned int nslice);
private:
	GridMeshPtr grid;

	inline GridMeshPtr CreateGrid(unsigned int nstack, unsigned int nslice);
	inline std::vector<Vertex3D>& GetVerticeList(unsigned int nstack, unsigned int nslice);
	inline std::vector<unsigned int>& GetIncidenceList(unsigned int nstack, unsigned int nslice);
};

inline SpherePtr Sphere::Make(unsigned int nstack, unsigned int nslice)
{
	return SpherePtr(new Sphere(nstack, nslice));
}

inline std::vector<Vertex3D>& Sphere::GetVerticeList(unsigned int nstack, unsigned int nslice)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack, nslice);
	return grid->GetVerticeList();
}

inline std::vector<unsigned int>& Sphere::GetIncidenceList(unsigned int nstack, unsigned int nslice)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack, nslice);
	return grid->GetIncidenceList();
}